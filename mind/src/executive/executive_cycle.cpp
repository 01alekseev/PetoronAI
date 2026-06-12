/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_cycle.hpp"

namespace petoron_ai {

ExecutiveCycle build_executive_cycle(
    ExecutiveState state
) {
    ExecutiveCycle cycle;

    switch (state) {
        case ExecutiveState::Planning:
            cycle.planning = true;
            break;

        case ExecutiveState::Executing:
            cycle.execution = true;
            break;

        case ExecutiveState::Learning:
            cycle.learning = true;
            break;

        case ExecutiveState::Recovering:
            cycle.execution = true;
            break;

        case ExecutiveState::Idle:
            break;
    }

    return cycle;
}

}
