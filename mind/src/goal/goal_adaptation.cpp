/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_adaptation.hpp"

namespace petoron_ai {

void apply_goal_feedback(
    GoalAdaptationState& state,
    const std::string& goal,
    int utility
) {
    state.goal_priority[goal] += utility;
}

int get_goal_priority(
    const GoalAdaptationState& state,
    const std::string& goal
) {
    const auto it = state.goal_priority.find(goal);

    if (it == state.goal_priority.end()) {
        return 0;
    }

    return it->second;
}

}
