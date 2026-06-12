/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_priority_selector.hpp"

namespace petoron_ai {

std::string select_primary_goal(
    const GoalAdaptationState& state
) {
    std::string best_goal;
    int best_priority = 0;
    bool found = false;

    for (const auto& [goal, priority] : state.goal_priority) {
        if (!found || priority > best_priority) {
            best_goal = goal;
            best_priority = priority;
            found = true;
        }
    }

    return best_goal;
}

}
