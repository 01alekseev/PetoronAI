/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/reasoning_proof_input.hpp"

#include <cstdint>
#include <vector>

namespace petoron_ai {

std::vector<std::uint8_t> encode_reasoning_proof_input(
    const ReasoningProofInput& input
);

MemoryDigest commit_reasoning_proof_input(
    const ReasoningProofInput& input
);

}
