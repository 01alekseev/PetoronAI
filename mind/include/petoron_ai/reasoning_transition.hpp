/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/reasoning_rule.hpp"

namespace petoron_ai {

struct ReasoningTransition {
    MemoryDigest old_root;
    MemoryDigest new_root;
    ReasoningRule rule;
    MemoryNode left;
    MemoryNode right;
    MemoryNode conclusion;
};

ReasoningTransition apply_reasoning_transition(
    const MemoryGraph& old_graph,
    const MemoryNode& left,
    const MemoryNode& right,
    const ReasoningRule& rule
);

bool verify_reasoning_transition(
    const MemoryGraph& old_graph,
    const ReasoningTransition& transition
);

}
