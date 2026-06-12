/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_aware_policy_selection.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistics statistics;

    statistics.add({
        "exploration",
        "policy_a",
        3,
        7
    });

    statistics.add({
        "exploration",
        "policy_b",
        9,
        1
    });

    statistics.add({
        "safety",
        "policy_c",
        10,
        0
    });

    const auto& selected =
        select_best_policy_for_goal(
            statistics,
            "exploration"
        );

    if (selected.policy_id != "policy_b") {
        return EXIT_FAILURE;
    }

    if (selected.goal_type != "exploration") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
