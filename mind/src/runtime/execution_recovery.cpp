/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/execution_recovery.hpp"

namespace petoron_ai {

RecoveryAction determine_recovery_action(
    ExecutionStatus status
) {
    switch (status) {
        case ExecutionStatus::Failed:
            return RecoveryAction::SwitchStrategy;

        case ExecutionStatus::Running:
            return RecoveryAction::None;

        case ExecutionStatus::Completed:
            return RecoveryAction::None;

        case ExecutionStatus::Pending:
            return RecoveryAction::Retry;
    }

    return RecoveryAction::None;
}

}
