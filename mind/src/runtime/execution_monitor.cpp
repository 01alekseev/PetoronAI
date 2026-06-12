/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/execution_monitor.hpp"

namespace petoron_ai {

ExecutionMonitor update_execution_monitor(
    ExecutionStatus status
) {
    ExecutionMonitor monitor;

    monitor.status = status;

    monitor.finished =
        status == ExecutionStatus::Completed ||
        status == ExecutionStatus::Failed;

    return monitor;
}

}
