/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/experience/self_improvement.hpp"

namespace petoron_ai {

void apply_outcome_feedback(
    SelfImprovementState& state,
    const std::string& action,
    int utility
) {
    state.action_confidence[action] += utility;
}

int get_action_confidence(
    const SelfImprovementState& state,
    const std::string& action
) {
    const auto it = state.action_confidence.find(action);

    if (it == state.action_confidence.end()) {
        return 0;
    }

    return it->second;
}

}
