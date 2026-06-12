/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_analytics.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutiveTransitionLog log;

    log.record(ExecutiveState::Idle);
    log.record(ExecutiveState::Planning);
    log.record(ExecutiveState::Planning);
    log.record(ExecutiveState::Executing);
    log.record(ExecutiveState::Recovering);
    log.record(ExecutiveState::Learning);

    const auto stats =
        analyze_transitions(log);

    if (stats.idle_count != 1) {
        return EXIT_FAILURE;
    }

    if (stats.planning_count != 2) {
        return EXIT_FAILURE;
    }

    if (stats.executing_count != 1) {
        return EXIT_FAILURE;
    }

    if (stats.recovering_count != 1) {
        return EXIT_FAILURE;
    }

    if (stats.learning_count != 1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
