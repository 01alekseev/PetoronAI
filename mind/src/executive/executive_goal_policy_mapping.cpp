/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_goal_policy_mapping.hpp"

namespace petoron_ai {

GoalPolicyMapping map_goal_to_policy(
    const std::string& goal_type
) {
    GoalPolicyMapping result;
    result.goal_type = goal_type;

    if (goal_type == "exploration") {
        result.preferred_planning_depth = 2;
        result.preferred_strategy_diversity = 3;
    } else if (goal_type == "safety") {
        result.preferred_planning_depth = 3;
        result.preferred_strategy_diversity = 1;
    } else if (goal_type == "optimization") {
        result.preferred_planning_depth = 2;
        result.preferred_strategy_diversity = 2;
    }

    return result;
}

}
