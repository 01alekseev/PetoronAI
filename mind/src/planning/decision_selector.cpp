/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/decision_selector.hpp"

namespace petoron_ai {

std::string select_best_hypothesis(
    const std::vector<EvaluatedHypothesis>& hypotheses
) {
    if (hypotheses.empty()) {
        return {};
    }

    const EvaluatedHypothesis* best = &hypotheses.front();

    for (const auto& hypothesis : hypotheses) {
        if (hypothesis.score > best->score) {
            best = &hypothesis;
        }
    }

    return best->hypothesis;
}

}
