/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/runtime/execution_monitor.hpp"

namespace petoron_ai {

enum class RecoveryAction {
    None,
    Retry,
    SwitchStrategy
};

RecoveryAction determine_recovery_action(
    ExecutionStatus status
);

}
