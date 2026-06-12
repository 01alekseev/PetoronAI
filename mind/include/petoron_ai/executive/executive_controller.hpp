/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

enum class ExecutiveState {
    Idle,
    Planning,
    Executing,
    Recovering,
    Learning
};

struct ExecutiveController {
    ExecutiveState state =
        ExecutiveState::Idle;
};

ExecutiveController transition_executive_state(
    ExecutiveState current,
    bool execution_failed,
    bool execution_completed
);

}
