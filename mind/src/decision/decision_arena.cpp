/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/decision/decision_arena.hpp"

#include <stdexcept>

namespace petoron_ai {

static int score_candidate(
    const DecisionCandidate& candidate
) {
    return
        candidate.survival_score * 5 +
        candidate.safety_score * 4 +
        candidate.resource_score * 3 +
        candidate.knowledge_score * 2 +
        candidate.risk_reduction_score * 5;
}

bool try_run_decision_arena(
    const std::vector<DecisionCandidate>& candidates,
    DecisionResult& result
) {
    if (candidates.empty()) {
        result = DecisionResult{};
        return false;
    }

    bool found = false;
    int best_score = 0;

    for (const auto& candidate : candidates) {
        const int score =
            score_candidate(candidate);

        if (!found || score > best_score) {
            found = true;
            best_score = score;
            result.selected_goal = candidate.goal;
            result.score = score;
        }
    }

    result.explanation =
        "selected highest weighted multi-objective score";

    return true;
}

DecisionResult run_decision_arena(
    const std::vector<DecisionCandidate>& candidates
) {
    DecisionResult result;

    if (!try_run_decision_arena(candidates, result)) {
        throw std::out_of_range("empty decision arena");
    }

    return result;
}

}
