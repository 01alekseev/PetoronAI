/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_configuration.hpp"

namespace petoron_ai {

struct ExecutiveRuntimeState {
    int planner_depth = 1;
    int strategy_candidates = 1;
    bool extra_validation = false;
};

ExecutiveRuntimeState apply_executive_configuration(
    const ExecutiveConfiguration& configuration
);

}
