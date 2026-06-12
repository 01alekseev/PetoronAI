/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_orchestrator.hpp"

namespace petoron_ai {

ExecutiveTickResult execute_mind_tick(
    ExecutiveState state
) {
    ExecutiveTickResult result;

    switch (state) {
        case ExecutiveState::Planning:
            result.planning = true;
            break;

        case ExecutiveState::Executing:
            result.execution = true;
            break;

        case ExecutiveState::Learning:
            result.learning = true;
            break;

        case ExecutiveState::Recovering:
            result.execution = true;
            break;

        case ExecutiveState::Idle:
            break;
    }

    return result;
}

}
