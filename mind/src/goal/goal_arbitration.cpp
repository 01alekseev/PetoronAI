/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_arbitration.hpp"

namespace petoron_ai {

PrioritizedGoal select_active_goal(
    const std::vector<PrioritizedGoal>& goals
) {
    PrioritizedGoal best;

    if (goals.empty()) {
        return best;
    }

    best = goals.front();

    for (const auto& goal : goals) {
        if (goal.priority > best.priority) {
            best = goal;
        }
    }

    return best;
}

}
