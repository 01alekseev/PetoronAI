/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_transition_log.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutiveTransitionLog log;

    log.record(
        ExecutiveState::Idle
    );

    log.record(
        ExecutiveState::Planning
    );

    log.record(
        ExecutiveState::Executing
    );

    if (log.size() != 3) {
        return EXIT_FAILURE;
    }

    const auto& history =
        log.history();

    if (
        history[0] != ExecutiveState::Idle
    ) {
        return EXIT_FAILURE;
    }

    if (
        history[1] != ExecutiveState::Planning
    ) {
        return EXIT_FAILURE;
    }

    if (
        history[2] != ExecutiveState::Executing
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
