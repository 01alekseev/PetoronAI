/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/outcome_evaluation.hpp"

namespace petoron_ai {

OutcomeEvaluation evaluate_outcome(
    const std::string& outcome
) {
    OutcomeEvaluation result;

    if (outcome == "safe shelter reached") {
        result.goal_achieved = true;
        result.utility = 100;
    } else if (outcome == "area evacuated") {
        result.goal_achieved = true;
        result.utility = 80;
    } else if (outcome == "storm survived") {
        result.goal_achieved = true;
        result.utility = 60;
    } else {
        result.goal_achieved = false;
        result.utility = 0;
    }

    return result;
}

}
