/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_runtime_configuration.hpp"

namespace petoron_ai {

ExecutiveRuntimeState apply_executive_configuration(
    const ExecutiveConfiguration& configuration
) {
    ExecutiveRuntimeState state;

    state.planner_depth =
        configuration.planner_depth;

    state.strategy_candidates =
        configuration.strategy_candidates;

    state.extra_validation =
        configuration.extra_validation;

    return state;
}

}
