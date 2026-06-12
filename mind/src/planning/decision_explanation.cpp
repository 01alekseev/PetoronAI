/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/decision_explanation.hpp"

namespace petoron_ai {

DecisionExplanation explain_decision(
    const std::string& selected_action,
    const std::string& reason,
    int confidence
) {
    DecisionExplanation result;

    result.selected_action = selected_action;
    result.reason = reason;
    result.confidence = confidence;

    return result;
}

}
