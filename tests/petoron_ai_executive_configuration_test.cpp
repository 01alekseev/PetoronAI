/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_configuration.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutivePolicy policy;

    policy.planning_depth = 3;
    policy.validation_level = 2;
    policy.strategy_diversity = 4;

    const auto config =
        build_executive_configuration(
            policy
        );

    if (config.planner_depth != 3) {
        return EXIT_FAILURE;
    }

    if (config.strategy_candidates != 4) {
        return EXIT_FAILURE;
    }

    if (!config.extra_validation) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
