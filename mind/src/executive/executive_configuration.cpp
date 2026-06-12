/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_configuration.hpp"

namespace petoron_ai {

ExecutiveConfiguration build_executive_configuration(
    const ExecutivePolicy& policy
) {
    ExecutiveConfiguration config;

    config.planner_depth =
        policy.planning_depth;

    config.strategy_candidates =
        policy.strategy_diversity;

    config.extra_validation =
        policy.validation_level > 1;

    return config;
}

}
