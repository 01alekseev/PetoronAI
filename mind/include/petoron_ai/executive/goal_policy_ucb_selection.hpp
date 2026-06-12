/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/goal_policy_statistics.hpp"

#include <cstddef>
#include <string>

namespace petoron_ai {

bool try_select_ucb_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type,
    double exploration_weight,
    std::size_t& selected_index
);

const GoalPolicyStatistic& select_ucb_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type,
    double exploration_weight
);

}
