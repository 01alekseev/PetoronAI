/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_scheduler.hpp"

namespace petoron_ai {

GoalSchedule schedule_goals(
    const std::vector<std::string>& goal_stack
) {
    GoalSchedule schedule;

    if (goal_stack.empty()) {
        return schedule;
    }

    schedule.current_goal = goal_stack.front();

    for (std::size_t i = 1; i < goal_stack.size(); ++i) {
        if (i <= 2) {
            schedule.queued_goals.push_back(goal_stack[i]);
        } else {
            schedule.deferred_goals.push_back(goal_stack[i]);
        }
    }

    return schedule;
}

}
