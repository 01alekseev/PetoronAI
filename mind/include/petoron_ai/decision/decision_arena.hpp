/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct DecisionCandidate {
    std::string goal;

    int survival_score = 0;
    int safety_score = 0;
    int resource_score = 0;
    int knowledge_score = 0;
    int risk_reduction_score = 0;
};

struct DecisionResult {
    std::string selected_goal;
    std::string explanation;
    int score = 0;
};

bool try_run_decision_arena(
    const std::vector<DecisionCandidate>& candidates,
    DecisionResult& result
);

DecisionResult run_decision_arena(
    const std::vector<DecisionCandidate>& candidates
);

}
