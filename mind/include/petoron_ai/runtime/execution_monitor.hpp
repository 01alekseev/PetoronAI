/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

enum class ExecutionStatus {
    Pending,
    Running,
    Completed,
    Failed
};

struct ExecutionMonitor {
    ExecutionStatus status =
        ExecutionStatus::Pending;

    bool finished = false;
};

ExecutionMonitor update_execution_monitor(
    ExecutionStatus status
);

}
