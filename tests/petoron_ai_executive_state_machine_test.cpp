/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_state_machine.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    if (
        next_executive_state(
            ExecutiveState::Idle,
            false,
            false,
            false
        ) != ExecutiveState::Planning
    ) {
        return EXIT_FAILURE;
    }

    if (
        next_executive_state(
            ExecutiveState::Planning,
            true,
            false,
            false
        ) != ExecutiveState::Executing
    ) {
        return EXIT_FAILURE;
    }

    if (
        next_executive_state(
            ExecutiveState::Executing,
            false,
            true,
            false
        ) != ExecutiveState::Learning
    ) {
        return EXIT_FAILURE;
    }

    if (
        next_executive_state(
            ExecutiveState::Executing,
            false,
            false,
            true
        ) != ExecutiveState::Recovering
    ) {
        return EXIT_FAILURE;
    }

    if (
        next_executive_state(
            ExecutiveState::Recovering,
            false,
            false,
            false
        ) != ExecutiveState::Planning
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
