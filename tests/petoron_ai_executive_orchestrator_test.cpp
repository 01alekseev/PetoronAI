/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_orchestrator.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    const auto planning =
        execute_mind_tick(
            ExecutiveState::Planning
        );

    if (!planning.planning) {
        return EXIT_FAILURE;
    }

    const auto execution =
        execute_mind_tick(
            ExecutiveState::Executing
        );

    if (!execution.execution) {
        return EXIT_FAILURE;
    }

    const auto learning =
        execute_mind_tick(
            ExecutiveState::Learning
        );

    if (!learning.learning) {
        return EXIT_FAILURE;
    }

    const auto idle =
        execute_mind_tick(
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
