/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_policy.hpp"

namespace petoron_ai {

struct ExecutiveConfiguration {
    int planner_depth = 1;
    int strategy_candidates = 1;
    bool extra_validation = false;
};

ExecutiveConfiguration build_executive_configuration(
    const ExecutivePolicy& policy
);

}
