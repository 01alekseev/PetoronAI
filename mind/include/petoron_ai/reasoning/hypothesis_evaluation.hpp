/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct EvaluatedHypothesis {
    std::string hypothesis;
    int score = 0;
};

std::vector<EvaluatedHypothesis> evaluate_hypotheses(
    const std::vector<std::string>& hypotheses
);

}
