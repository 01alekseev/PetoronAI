/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct GoalSchedule {
    std::string current_goal;
    std::vector<std::string> queued_goals;
    std::vector<std::string> deferred_goals;
};

GoalSchedule schedule_goals(
    const std::vector<std::string>& goal_stack
);

}
