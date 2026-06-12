/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_node.hpp"

#include <cstdint>

namespace petoron_ai {

struct MindState {
    MemoryDigest current_kb_id;
    MemoryDigest transition_chain_id;
    MemoryDigest last_cycle_id;
    std::uint64_t cycle_count = 0;
};

MemoryDigest commit_mind_state(
    const MindState& state
);

}
