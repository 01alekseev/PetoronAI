/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <unordered_map>

namespace petoron_ai {

struct GoalAdaptationState {
    std::unordered_map<std::string, int> goal_priority;
};

void apply_goal_feedback(
    GoalAdaptationState& state,
    const std::string& goal,
    int utility
);

int get_goal_priority(
    const GoalAdaptationState& state,
    const std::string& goal
);

}
