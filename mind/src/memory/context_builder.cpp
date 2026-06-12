/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/context_builder.hpp"

namespace petoron_ai {

Context build_context(
    const std::vector<MemoryItem>& memories
) {
    Context context;

    for (const auto& memory : memories) {
        context.facts.push_back(memory.fact);
    }

    return context;
}

}
