/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/execution_monitor.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    const auto running =
        update_execution_monitor(
            ExecutionStatus::Running
        );

    if (running.finished) {
        return EXIT_FAILURE;
    }

    const auto completed =
        update_execution_monitor(
            ExecutionStatus::Completed
        );

    if (!completed.finished) {
        return EXIT_FAILURE;
    }

    const auto failed =
        update_execution_monitor(
            ExecutionStatus::Failed
        );

    if (!failed.finished) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
