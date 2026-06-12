/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

struct DecisionExplanation {
    std::string selected_action;
    std::string reason;
    int confidence = 0;
};

DecisionExplanation explain_decision(
    const std::string& selected_action,
    const std::string& reason,
    int confidence
);

}
