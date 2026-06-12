/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_ucb_selection.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistics statistics;

    statistics.add({
        "survive",
        "stable_policy",
        90,
        10
    });

    statistics.add({
        "survive",
        "new_promising_policy",
        1,
        0
    });

    statistics.add({
        "survive",
        "bad_policy",
        0,
        10
    });

    const auto& selected =
        select_ucb_policy_for_goal(
            statistics,
            "survive",
            0.75
        );

    if (selected.policy_id != "new_promising_policy") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
