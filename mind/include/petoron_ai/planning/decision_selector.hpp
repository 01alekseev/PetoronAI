/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/reasoning/hypothesis_evaluation.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

std::string select_best_hypothesis(
    const std::vector<EvaluatedHypothesis>& hypotheses
);

}
