/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/reasoning_trace_codec.hpp"

namespace petoron_ai {

struct ReasoningProofInput {
    MemoryDigest old_root;
    MemoryDigest new_root;
    MemoryDigest trace_id;
};

ReasoningProofInput build_reasoning_proof_input(
    const ReasoningTrace& trace
);

bool verify_reasoning_proof_input(
    const ReasoningTrace& trace,
    const ReasoningProofInput& input
);

}
