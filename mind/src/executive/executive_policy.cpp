/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy.hpp"

namespace petoron_ai {

ExecutivePolicy build_executive_policy(
    const ExecutiveOptimization& optimization
) {
    ExecutivePolicy policy;

    if (optimization.increase_planning) {
        policy.planning_depth = 2;
    }

    if (optimization.reduce_recovery) {
        policy.validation_level = 2;
        policy.strategy_diversity = 2;
    }

    return policy;
}

}
