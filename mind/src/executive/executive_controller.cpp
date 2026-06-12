/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_controller.hpp"

namespace petoron_ai {

ExecutiveController transition_executive_state(
    ExecutiveState current,
    bool execution_failed,
    bool execution_completed
) {
    ExecutiveController controller;

    if (execution_failed) {
        controller.state =
            ExecutiveState::Recovering;
        return controller;
    }

    if (execution_completed) {
        controller.state =
            ExecutiveState::Learning;
        return controller;
    }

    controller.state = current;
    return controller;
}

}
