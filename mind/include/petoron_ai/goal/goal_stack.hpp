/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/goal/goal_adaptation.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

std::vector<std::string> build_goal_stack(
    const GoalAdaptationState& state
);

}
