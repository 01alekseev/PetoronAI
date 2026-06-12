/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/goal_resolver.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct FutureOutcome {
    std::string action;
    std::string future_state;
    int risk_score = 0;
};

std::vector<FutureOutcome> simulate_goal(
    const GoalResolution& resolution
);

}
