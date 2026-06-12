/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/execution_recovery.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    if (
        determine_recovery_action(
            ExecutionStatus::Failed
        ) != RecoveryAction::SwitchStrategy
    ) {
        return EXIT_FAILURE;
    }

    if (
        determine_recovery_action(
            ExecutionStatus::Pending
        ) != RecoveryAction::Retry
    ) {
        return EXIT_FAILURE;
    }

    if (
        determine_recovery_action(
            ExecutionStatus::Running
        ) != RecoveryAction::None
    ) {
        return EXIT_FAILURE;
    }

    if (
        determine_recovery_action(
            ExecutionStatus::Completed
        ) != RecoveryAction::None
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
