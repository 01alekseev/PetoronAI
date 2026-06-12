/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutiveOptimization optimization;

    optimization.increase_planning = true;
    optimization.reduce_recovery = true;

    const auto policy =
        build_executive_policy(
            optimization
        );

    if (policy.planning_depth != 2) {
        return EXIT_FAILURE;
    }

    if (policy.validation_level != 2) {
        return EXIT_FAILURE;
    }

    if (policy.strategy_diversity != 2) {
        return EXIT_FAILURE;
    }

    ExecutiveOptimization neutral;

    const auto default_policy =
        build_executive_policy(
            neutral
        );

    if (default_policy.planning_depth != 1) {
        return EXIT_FAILURE;
    }

    if (default_policy.validation_level != 1) {
        return EXIT_FAILURE;
    }

    if (default_policy.strategy_diversity != 1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
