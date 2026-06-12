/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/reasoning_proof_input_codec.hpp"

namespace petoron_ai {

struct ReasoningProofPackage {
    ReasoningTrace trace;
    ReasoningProofInput input;
    MemoryDigest statement_id;
};

ReasoningProofPackage build_reasoning_proof_package(
    const ReasoningTransition& transition
);

bool verify_reasoning_proof_package(
    const ReasoningProofPackage& package
);

}
