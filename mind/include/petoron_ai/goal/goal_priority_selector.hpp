/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/goal/goal_adaptation.hpp"

#include <string>

namespace petoron_ai {

std::string select_primary_goal(
    const GoalAdaptationState& state
);

}
