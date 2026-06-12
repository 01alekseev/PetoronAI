/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

struct GoalPolicyMapping {
    std::string goal_type;
    int preferred_planning_depth = 1;
    int preferred_strategy_diversity = 1;
};

GoalPolicyMapping map_goal_to_policy(
    const std::string& goal_type
);

}
