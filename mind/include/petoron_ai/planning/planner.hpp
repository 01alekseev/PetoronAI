/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/planning/goal_tree.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct PlanStep {
    std::string goal;
    std::string action;
};

std::vector<PlanStep> build_plan(
    const GoalNode& tree
);

}
