/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/goal/goal_coalition.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct GoalConflict {
    std::string winner;
    std::string loser;
};

GoalConflict resolve_goal_conflict(
    const PrioritizedGoal& left,
    const PrioritizedGoal& right
);

}
