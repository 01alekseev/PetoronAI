/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_state_machine.hpp"

namespace petoron_ai {

ExecutiveState next_executive_state(
    ExecutiveState current,
    bool planning_complete,
    bool execution_complete,
    bool execution_failed
) {
    if (execution_failed) {
        return ExecutiveState::Recovering;
    }

    switch (current) {
        case ExecutiveState::Idle:
            return ExecutiveState::Planning;

        case ExecutiveState::Planning:
            return planning_complete
                ? ExecutiveState::Executing
                : ExecutiveState::Planning;

        case ExecutiveState::Executing:
            return execution_complete
                ? ExecutiveState::Learning
                : ExecutiveState::Executing;

        case ExecutiveState::Learning:
            return ExecutiveState::Planning;

        case ExecutiveState::Recovering:
            return ExecutiveState::Planning;
    }

    return ExecutiveState::Idle;
}

}
