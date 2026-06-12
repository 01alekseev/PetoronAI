/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory/long_term_memory.hpp"

#include <vector>

namespace petoron_ai {

std::vector<MemoryItem> select_attention_memories(
    const LongTermMemory& memory,
    std::size_t limit
);

}
