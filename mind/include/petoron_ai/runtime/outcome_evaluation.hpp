/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

struct OutcomeEvaluation {
    bool goal_achieved = false;
    int utility = 0;
};

OutcomeEvaluation evaluate_outcome(
    const std::string& outcome
);

}
