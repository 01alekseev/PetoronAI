/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/goal_policy_statistics.hpp"
#include "petoron_ai/executive/goal_policy_safety_filter.hpp"

#include <string>

namespace petoron_ai {

const GoalPolicyStatistic& select_safe_ucb_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type,
    double exploration_weight,
    const ExecutiveSafetyState& state
);

}
