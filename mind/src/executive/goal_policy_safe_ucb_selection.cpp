/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_safe_ucb_selection.hpp"

#include "petoron_ai/executive/goal_policy_confidence.hpp"
#include "petoron_ai/executive/goal_policy_evidence.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace petoron_ai {

static double state_policy_bonus(
    const ExecutiveSafetyState& state,
    const std::string& policy_id
) {
    if (policy_id == "reduce_risk") {
        if (state.risk >= 70) return 1.00;
        if (state.risk >= 50) return 0.45;
        if (state.risk >= 30) return 0.10;
        return -0.35;
    }

    if (policy_id == "secure_shelter") {
        if (state.safety < 70) return 0.75;
        if (state.risk >= 50) return 0.25;
        return -0.05;
    }

    if (policy_id == "collect_resources") {
        if (state.resources <= 20) return 1.00;
        if (state.resources <= 50) return 0.55;
        if (state.resources >= 90) return -0.35;
        if (state.risk >= 50) return -0.20;
        return 0.15;
    }

    if (policy_id == "observe_environment") {
        if (state.knowledge < 50) return 0.85;
        if (state.knowledge < 90) return 0.35;
        if (state.risk >= 30) return 0.15;
        return -0.25;
    }

    if (policy_id == "maintain_stability") {
        if (
            state.survival >= 90 &&
            state.safety >= 90 &&
            state.resources >= 80 &&
            state.knowledge >= 90 &&
            state.risk <= 25
        ) {
            return 1.20;
        }

        return -1.00;
    }

    return 0.0;
}

const GoalPolicyStatistic& select_safe_ucb_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type,
    double exploration_weight,
    const ExecutiveSafetyState& state
) {
    if (statistics.size() == 0) {
        throw std::out_of_range("empty statistics");
    }

    if (exploration_weight < 0.0) {
        exploration_weight = 0.0;
    }

    std::size_t total_observations = 0;

    for (std::size_t i = 0; i < statistics.size(); ++i) {
        const auto& entry = statistics.at(i);

        if (entry.goal_type != goal_type) {
            continue;
        }

        total_observations +=
            entry.success_count +
            entry.failure_count;
    }

    double best_score =
        -std::numeric_limits<double>::infinity();

    std::size_t best_index = 0;
    bool found = false;

    for (std::size_t i = 0; i < statistics.size(); ++i) {
        const auto& entry = statistics.at(i);

        if (entry.goal_type != goal_type) {
            continue;
        }

        if (
            !is_policy_safe(
                state,
                entry.policy_id
            )
        ) {
            continue;
        }

        const auto observations =
            entry.success_count +
            entry.failure_count;

        const double confidence =
            calculate_goal_policy_confidence(
                entry
            );

        const double evidence =
            calculate_goal_policy_evidence(
                entry
            );

        if (
            entry.policy_id == "maintain_stability" &&
            !(
                state.survival >= 90 &&
                state.safety >= 90 &&
                state.resources >= 80 &&
                state.knowledge >= 90 &&
                state.risk <= 25
            ) &&
            evidence >= 0.80 &&
            confidence < 0.20
        ) {
            continue;
        }

        const double mean =
            static_cast<double>(entry.success_count + 1) /
            static_cast<double>(observations + 2);

        const double exploration =
            exploration_weight *
            std::sqrt(
                std::log(
                    static_cast<double>(
                        total_observations + 1
                    )
                ) /
                static_cast<double>(
                    observations + 1
                )
            );

        const double dominance_penalty =
            0.08 *
            std::sqrt(
                static_cast<double>(observations) /
                static_cast<double>(total_observations + 1)
            );

        const double score =
            mean +
            exploration +
            state_policy_bonus(
                state,
                entry.policy_id
            ) -
            dominance_penalty;

        if (
            !found ||
            score > best_score
        ) {
            found = true;
            best_score = score;
            best_index = i;
        }
    }

    if (!found) {
        const char* fallback_policy_id =
            "observe_environment";

        if (state.risk >= 70) {
            fallback_policy_id =
                "reduce_risk";
        } else if (state.resources <= 20) {
            fallback_policy_id =
                "collect_resources";
        } else if (state.safety < 70) {
            fallback_policy_id =
                "secure_shelter";
        }

        for (std::size_t i = 0; i < statistics.size(); ++i) {
            const auto& entry = statistics.at(i);

            if (
                entry.goal_type == goal_type &&
                entry.policy_id == fallback_policy_id
            ) {
                return statistics.at(i);
            }
        }

        throw std::out_of_range("no safe policy");
    }

    return statistics.at(best_index);
}

}
