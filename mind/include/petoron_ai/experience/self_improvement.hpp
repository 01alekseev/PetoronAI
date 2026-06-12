/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <unordered_map>

namespace petoron_ai {

struct SelfImprovementState {
    std::unordered_map<std::string, int> action_confidence;
};

void apply_outcome_feedback(
    SelfImprovementState& state,
    const std::string& action,
    int utility
);

int get_action_confidence(
    const SelfImprovementState& state,
    const std::string& action
);

}
