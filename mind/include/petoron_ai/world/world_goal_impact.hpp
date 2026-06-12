/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/agent_cycle.hpp"
#include "petoron_ai/world/world_model.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct GoalImpact {
    std::string subject;
    std::string relation;
    std::string object;
    std::string goal;
    int impact_score = 0;
    bool positive = false;
};

std::vector<GoalImpact> evaluate_goal_impact(
    const WorldModel& model,
    const Goal& goal
);

}
