/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/long_term_memory.hpp"

namespace petoron_ai {

void remember_fact(
    LongTermMemory& memory,
    const std::string& fact,
    int strength
) {
    if (fact.empty()) {
        return;
    }

    for (auto& item : memory.items) {
        if (item.fact == fact) {
            item.strength += strength;
            return;
        }
    }

    MemoryItem item;
    item.fact = fact;
    item.strength = strength;
    memory.items.push_back(item);
}

const MemoryItem* find_memory_item(
    const LongTermMemory& memory,
    const std::string& fact
) {
    for (const auto& item : memory.items) {
        if (item.fact == fact) {
            return &item;
        }
    }

    return nullptr;
}

}
