/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/runtime_input.hpp"
#include "petoron_ai/knowledge/knowledge_store.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct GoalResolutionCandidate {
    std::string target;
    std::string goal;
    std::string reason;
    int base = 0;
    int confidence = 0;
    int strategy = 0;
    int experience = 0;
    int score = 0;
};

struct GoalResolution {
    std::string resolved_goal;
    std::string resolved_reason;
    int resolved_score = 0;
    std::vector<GoalResolutionCandidate> candidates;
};

GoalResolution resolve_goal_trace(
    const KnowledgeStore& kb,
    const RuntimeInput& input
);

std::string resolve_goal(
    const KnowledgeStore& kb,
    const RuntimeInput& input
);

}
