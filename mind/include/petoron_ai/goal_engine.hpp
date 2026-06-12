/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/petoron_mind.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct Goal {
    std::string name;
};

struct PlanStep {
    std::string action;
    std::string reason;
};

struct Plan {
    Goal goal;
    std::vector<PlanStep> steps;
};

Plan build_plan(
    const PetoronMind& mind,
    const Goal& goal
);

}
