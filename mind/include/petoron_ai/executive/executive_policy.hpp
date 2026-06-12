/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_optimization.hpp"

namespace petoron_ai {

struct ExecutivePolicy {
    int planning_depth = 1;
    int validation_level = 1;
    int strategy_diversity = 1;
};

ExecutivePolicy build_executive_policy(
    const ExecutiveOptimization& optimization
);

}
