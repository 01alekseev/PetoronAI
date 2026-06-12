/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_safe_ucb_selection.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistics stats;

    stats.add({
        "survival",
        "reduce_risk",
        10,
        2
    });

    stats.add({
        "survival",
        "collect_resources",
        10,
        2
    });

    stats.add({
        "survival",
        "observe_environment",
        10,
        2
    });

    ExecutiveSafetyState state;

    state.survival = 80;
    state.resources = 50;
    state.risk = 90;

    const auto& selected =
        select_safe_ucb_policy_for_goal(
            stats,
            "survival",
            0.85,
            state
        );

    if (
        selected.policy_id ==
        "collect_resources"
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
