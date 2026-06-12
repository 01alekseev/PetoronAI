/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/decision/decision_arena.hpp"
#include "petoron_ai/executive/goal_policy_ucb_selection.hpp"
#include "petoron_ai/executive/goal_aware_policy_selection.hpp"
#include "petoron_ai/executive/executive_policy_selection.hpp"
#include "petoron_ai/executive/executive_policy_history.hpp"

#include <cstdlib>
#include <stdexcept>
#include <vector>

int main() {
    using namespace petoron_ai;

    {
        GoalPolicyStatistics stats;
        std::size_t index = 99;

        if (try_select_ucb_policy_for_goal(stats, "missing", 0.85, index)) {
            return EXIT_FAILURE;
        }
    }

    {
        GoalPolicyStatistics stats;
        stats.add({"survive", "policy_a", 1, 0});

        std::size_t index = 99;

        if (try_select_ucb_policy_for_goal(stats, "missing", 0.85, index)) {
            return EXIT_FAILURE;
        }
    }

    {
        GoalPolicyStatistics stats;
        stats.add({"survive", "policy_a", 1, 0});

        bool thrown = false;

        try {
            (void)select_ucb_policy_for_goal(stats, "missing", 0.85);
        } catch (const std::out_of_range&) {
            thrown = true;
        }

        if (!thrown) {
            return EXIT_FAILURE;
        }
    }

    {
        GoalPolicyStatistics stats;
        std::size_t index = 99;

        if (try_select_best_policy_for_goal(stats, "survive", index)) {
            return EXIT_FAILURE;
        }
    }

    {
        ExecutivePolicyHistory history;
        std::size_t index = 99;

        if (try_select_best_policy(history, index)) {
            return EXIT_FAILURE;
        }
    }

    {
        DecisionResult result;

        if (try_run_decision_arena({}, result)) {
            return EXIT_FAILURE;
        }
    }

    {
        bool thrown = false;

        try {
            (void)run_decision_arena({});
        } catch (const std::out_of_range&) {
            thrown = true;
        }

        if (!thrown) {
            return EXIT_FAILURE;
        }
    }

    {
        std::vector<DecisionCandidate> candidates = {
            {"collect resources", 0, 0, 30, 0, 0},
            {"reduce risk", 20, 25, 0, 0, 40}
        };

        const auto result =
            run_decision_arena(candidates);

        if (result.selected_goal != "reduce risk") {
            return EXIT_FAILURE;
        }

        if (result.explanation.empty()) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
