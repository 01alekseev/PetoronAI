/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/reasoning_transition.hpp"

namespace petoron_ai {

struct ReasoningTrace {
    MemoryDigest old_root;
    MemoryDigest new_root;
    MemoryDigest left_commitment;
    MemoryDigest right_commitment;
    MemoryDigest conclusion_commitment;
    std::string rule_name;
};

ReasoningTrace build_reasoning_trace(
    const ReasoningTransition& transition
);

bool verify_reasoning_trace(
    const ReasoningTransition& transition,
    const ReasoningTrace& trace
);

}
