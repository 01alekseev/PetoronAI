/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_runtime_configuration.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutiveConfiguration configuration;

    configuration.planner_depth = 5;
    configuration.strategy_candidates = 3;
    configuration.extra_validation = true;

    const auto runtime =
        apply_executive_configuration(
            configuration
        );

    if (runtime.planner_depth != 5) {
        return EXIT_FAILURE;
    }

    if (runtime.strategy_candidates != 3) {
        return EXIT_FAILURE;
    }

    if (!runtime.extra_validation) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
