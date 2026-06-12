/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_controller.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    const auto failed =
        transition_executive_state(
            ExecutiveState::Executing,
            true,
            false
        );

    if (
        failed.state !=
        ExecutiveState::Recovering
    ) {
        return EXIT_FAILURE;
    }

    const auto completed =
        transition_executive_state(
            ExecutiveState::Executing,
            false,
            true
        );

    if (
        completed.state !=
        ExecutiveState::Learning
    ) {
        return EXIT_FAILURE;
    }

    const auto running =
        transition_executive_state(
            ExecutiveState::Executing,
            false,
            false
        );

    if (
        running.state !=
        ExecutiveState::Executing
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
