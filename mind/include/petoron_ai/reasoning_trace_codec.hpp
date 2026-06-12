/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/reasoning_trace.hpp"

#include <cstdint>
#include <vector>

namespace petoron_ai {

std::vector<std::uint8_t> encode_reasoning_trace(
    const ReasoningTrace& trace
);

MemoryDigest commit_reasoning_trace(
    const ReasoningTrace& trace
);

}
