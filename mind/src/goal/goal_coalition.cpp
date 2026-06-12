/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_coalition.hpp"

namespace petoron_ai {

GoalCoalition build_goal_coalition(
    const std::vector<PrioritizedGoal>& goals,
    int minimum_priority
) {
    GoalCoalition coalition;

    for (const auto& goal : goals) {
        if (goal.priority < minimum_priority) {
            continue;
        }

        coalition.goals.push_back(goal);
        coalition.total_priority += goal.priority;
    }

    return coalition;
}

}
