/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning_proof_input.hpp"

namespace petoron_ai {

ReasoningProofInput build_reasoning_proof_input(
    const ReasoningTrace& trace
) {
    ReasoningProofInput input;
    input.old_root = trace.old_root;
    input.new_root = trace.new_root;
    input.trace_id = commit_reasoning_trace(trace);
    return input;
}

bool verify_reasoning_proof_input(
    const ReasoningTrace& trace,
    const ReasoningProofInput& input
) {
    if (input.old_root != trace.old_root) {
        return false;
    }

    if (input.new_root != trace.new_root) {
        return false;
    }

    return input.trace_id == commit_reasoning_trace(trace);
}

}
