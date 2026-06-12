/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/attention_engine.hpp"

#include <algorithm>

namespace petoron_ai {

std::vector<MemoryItem> select_attention_memories(
    const LongTermMemory& memory,
    std::size_t limit
) {
    auto result = memory.items;

    std::sort(
        result.begin(),
        result.end(),
        [](const MemoryItem& a, const MemoryItem& b) {
            return a.strength > b.strength;
        }
    );

    if (result.size() > limit) {
        result.resize(limit);
    }

    return result;
}

}
