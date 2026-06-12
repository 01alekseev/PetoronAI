/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/agent_cycle.hpp"

#include <vector>

namespace petoron_ai {

struct PrioritizedGoal {
    Goal goal;
    int priority = 0;
};

PrioritizedGoal select_active_goal(
    const std::vector<PrioritizedGoal>& goals
);

}
