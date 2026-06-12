/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_cycle.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    const auto planning =
        build_executive_cycle(
            ExecutiveState::Planning
        );

    if (!planning.planning) {
        return EXIT_FAILURE;
    }

    const auto executing =
        build_executive_cycle(
            ExecutiveState::Executing
        );

    if (!executing.execution) {
        return EXIT_FAILURE;
    }

    const auto learning =
        build_executive_cycle(
            ExecutiveState::Learning
        );

    if (!learning.learning) {
        return EXIT_FAILURE;
    }

    const auto idle =
        build_executive_cycle(
            ExecutiveState::Idle
        );

    if (
        idle.planning ||
        idle.execution ||
        idle.learning
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
