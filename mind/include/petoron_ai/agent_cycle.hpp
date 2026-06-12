/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/feedback_engine.hpp"

namespace petoron_ai {

struct AgentCycleResult {
    Plan plan;
    std::vector<ActionResult> actions;
    std::vector<MemoryTransition> feedback;
    MemoryDigest final_root;
};

AgentCycleResult run_cycle(
    PetoronMind& mind,
    const Goal& goal,
    const std::vector<ReasoningRule>& rules
);

}
