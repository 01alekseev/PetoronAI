/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_goal_policy_mapping.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    const auto exploration =
        map_goal_to_policy(
            "exploration"
        );

    if (
        exploration.preferred_strategy_diversity != 3
    ) {
        return EXIT_FAILURE;
    }

    const auto safety =
        map_goal_to_policy(
            "safety"
        );

    if (
        safety.preferred_planning_depth != 3
    ) {
        return EXIT_FAILURE;
    }

    const auto optimization =
        map_goal_to_policy(
            "optimization"
        );

    if (
        optimization.preferred_strategy_diversity != 2
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
