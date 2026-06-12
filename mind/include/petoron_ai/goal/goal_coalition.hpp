/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/goal/goal_arbitration.hpp"

#include <vector>

namespace petoron_ai {

struct GoalCoalition {
    std::vector<PrioritizedGoal> goals;
    int total_priority = 0;
};

GoalCoalition build_goal_coalition(
    const std::vector<PrioritizedGoal>& goals,
    int minimum_priority
);

}
