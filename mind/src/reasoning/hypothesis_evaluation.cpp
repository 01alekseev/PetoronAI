/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning/hypothesis_evaluation.hpp"

namespace petoron_ai {

std::vector<EvaluatedHypothesis> evaluate_hypotheses(
    const std::vector<std::string>& hypotheses
) {
    std::vector<EvaluatedHypothesis> result;

    for (const auto& hypothesis : hypotheses) {
        EvaluatedHypothesis item;
        item.hypothesis = hypothesis;

        if (hypothesis == "find shelter") {
            item.score = 100;
        } else if (hypothesis == "leave area") {
            item.score = 80;
        } else if (hypothesis == "wait for storm to pass") {
            item.score = 40;
        } else {
            item.score = 10;
        }

        result.push_back(item);
    }

    return result;
}

}
