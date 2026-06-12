/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct MemoryItem {
    std::string fact;
    int strength = 0;
};

struct LongTermMemory {
    std::vector<MemoryItem> items;
};

void remember_fact(
    LongTermMemory& memory,
    const std::string& fact,
    int strength
);

const MemoryItem* find_memory_item(
    const LongTermMemory& memory,
    const std::string& fact
);

}
