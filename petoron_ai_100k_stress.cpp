/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/decision/decision_arena.hpp"
#include "petoron_ai/executive/executive_feedback.hpp"
#include "petoron_ai/executive/goal_policy_statistics.hpp"
#include "petoron_ai/executive/goal_policy_safe_ucb_selection.hpp"
#include "petoron_ai/executive/goal_policy_reinforcement.hpp"
#include "petoron_ai/executive/goal_policy_confidence.hpp"
#include "petoron_ai/executive/goal_policy_evidence.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct World {
    int survival = 75;
    int safety = 35;
    int resources = 15;
    int knowledge = 10;
    int risk = 85;
};

struct PolicyRuntime {
    std::string action;
    long long reward_total = 0;
    long long selected = 0;
};

static int clamp(int v) {
    if (v < 0) return 0;
    if (v > 100) return 100;
    return v;
}

static int utility(const World& w) {
    return
        w.survival * 5 +
        w.safety * 4 +
        w.resources * 3 +
        w.knowledge * 2 -
        w.risk * 5;
}

static int apply_world_action(
    World& w,
    const std::string& action
) {
    const int before = utility(w);

    if (action == "reduce immediate risk") {
        w.risk -= 28;
        w.safety += 10;
        w.resources -= 2;
    } else if (action == "secure shelter") {
        w.safety += 24;
        w.risk -= 18;
        w.resources -= 3;
    } else if (action == "collect resources") {
        w.resources += 24;

        if (w.risk < 70) {
            w.risk += 5;
        } else {
            w.risk += 14;
            w.survival -= 8;
        }
    } else if (action == "observe environment") {
        w.knowledge += 24;
        w.risk -= 7;
    } else if (action == "maintain stability") {
        if (
            w.survival >= 90 &&
            w.safety >= 90 &&
            w.resources >= 80 &&
            w.knowledge >= 90 &&
            w.risk <= 25
        ) {
            w.risk -= 3;
        } else {
            w.risk += 6;
            w.survival -= 3;
        }
    } else {
        w.risk += 10;
        w.survival -= 5;
    }

    w.risk += 2;
    w.resources -= 1;

    if (w.risk > 70) {
        w.survival -= 4;
    }

    if (
        w.safety > 70 &&
        w.resources > 30 &&
        w.knowledge > 40
    ) {
        w.survival += 2;
    }

    w.survival = clamp(w.survival);
    w.safety = clamp(w.safety);
    w.resources = clamp(w.resources);
    w.knowledge = clamp(w.knowledge);
    w.risk = clamp(w.risk);

    return (utility(w) - before) / 10;
}

static long long ms(
    std::chrono::steady_clock::time_point start
) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start
    ).count();
}

int main() {
    using namespace petoron_ai;
    using Clock = std::chrono::steady_clock;

    constexpr int rounds = 100000;

    const auto start = Clock::now();

    std::vector<DecisionCandidate> candidates = {
        {"reduce risk", 20, 25, 0, 0, 40},
        {"secure shelter", 10, 35, 0, 0, 20},
        {"collect resources", 0, 0, 30, 0, 0},
        {"observe environment", 0, 0, 0, 30, 10}
    };

    const auto decision =
        run_decision_arena(
            candidates
        );

    GoalPolicyStatistics stats;
    stats.add({"long_term_survival", "reduce_risk", 1, 1});
    stats.add({"long_term_survival", "secure_shelter", 1, 1});
    stats.add({"long_term_survival", "collect_resources", 1, 1});
    stats.add({"long_term_survival", "observe_environment", 1, 1});
    stats.add({"long_term_survival", "maintain_stability", 1, 1});

    std::map<std::string, PolicyRuntime> policies;
    policies["reduce_risk"] = {"reduce immediate risk"};
    policies["secure_shelter"] = {"secure shelter"};
    policies["collect_resources"] = {"collect resources"};
    policies["observe_environment"] = {"observe environment"};
    policies["maintain_stability"] = {"maintain stability"};

    World world;

    int min_survival = world.survival;
    bool printed_low_survival = false;
    int max_risk = world.risk;
    int min_utility = utility(world);
    int max_utility = utility(world);

    for (int round = 1; round <= rounds; ++round) {
        ExecutiveSafetyState safety;

        safety.survival =
            world.survival;

        safety.survival =
            world.survival;

        safety.safety =
            world.safety;

        safety.resources =
            world.resources;

        safety.knowledge =
            world.knowledge;

        safety.risk =
            world.risk;

        auto selected =
            select_safe_ucb_policy_for_goal(
                stats,
                "long_term_survival",
                0.85,
                safety
            );

        auto& runtime =
            policies[selected.policy_id];

        ++runtime.selected;

        const int reward =
            apply_world_action(
                world,
                runtime.action
            );

        runtime.reward_total += reward;

        const int magnitude =
            reward < 0
                ? -reward
                : reward;

        const auto feedback =
            evaluate_executive_feedback(
                reward > 0 ? magnitude : 0,
                reward < 0 ? magnitude : 0
            );

        reinforce_goal_policy(
            selected,
            feedback
        );

        GoalPolicyStatistics next;

        for (std::size_t i = 0; i < stats.size(); ++i) {
            const auto& item =
                stats.at(i);

            if (
                item.goal_type == selected.goal_type &&
                item.policy_id == selected.policy_id
            ) {
                next.add(selected);
            } else {
                next.add(item);
            }
        }

        stats = next;

        const int u =
            utility(world);

        if (world.survival < min_survival) {
            min_survival = world.survival;
        }

        if (
            !printed_low_survival &&
            world.survival < 40
        ) {
            printed_low_survival = true;

            std::cout
                << "TRACE:low_survival round=" << round
                << " survival=" << world.survival
                << " resources=" << world.resources
                << " risk=" << world.risk
                << " action=" << runtime.action
                << " reward=" << reward
                << std::endl;
        }

        if (world.risk > max_risk) {
            max_risk = world.risk;
        }

        if (u < min_utility) {
            min_utility = u;
        }

        if (u > max_utility) {
            max_utility = u;
        }

        if (
            world.survival < 1 ||
            world.risk > 99
        ) {
            std::cout
                << "FAIL:unstable_world round=" << round
                << " survival=" << world.survival
                << " risk=" << world.risk
                << " action=" << runtime.action
                << " reward=" << reward
                << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "=== PetoronAI 100k Stress ===" << std::endl;
    std::cout << "initial_decision=" << decision.selected_goal << std::endl;
    std::cout << "rounds=" << rounds << std::endl;
    std::cout << "time_ms=" << ms(start) << std::endl;
    std::cout << "min_survival=" << min_survival << std::endl;
    std::cout << "max_risk=" << max_risk << std::endl;
    std::cout << "min_utility=" << min_utility << std::endl;
    std::cout << "max_utility=" << max_utility << std::endl;

    std::cout << "=== Final World ===" << std::endl;
    std::cout << "survival=" << world.survival << std::endl;
    std::cout << "safety=" << world.safety << std::endl;
    std::cout << "resources=" << world.resources << std::endl;
    std::cout << "knowledge=" << world.knowledge << std::endl;
    std::cout << "risk=" << world.risk << std::endl;
    std::cout << "utility=" << utility(world) << std::endl;

    std::cout << "=== Policies ===" << std::endl;

    long long selected_total = 0;

    for (std::size_t i = 0; i < stats.size(); ++i) {
        const auto& item =
            stats.at(i);

        const auto& rt =
            policies[item.policy_id];

        selected_total += rt.selected;

        std::cout
            << item.policy_id
            << " selected=" << rt.selected
            << " reward_total=" << rt.reward_total
            << " confidence=" << calculate_goal_policy_confidence(item)
            << " evidence=" << calculate_goal_policy_evidence(item)
            << std::endl;
    }

    if (selected_total != rounds) {
        std::cout << "FAIL:selected_total_mismatch" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "PASS 100k stress" << std::endl;

    return EXIT_SUCCESS;
}
