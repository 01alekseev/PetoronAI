/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/goal_policy_statistics.hpp"

namespace petoron_ai {

double calculate_goal_policy_confidence(
    const GoalPolicyStatistic& statistic
);

}
