/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_mind_bridge.hpp"

namespace petoron_ai {

void load_knowledge_into_mind(
    const KnowledgeStore& store,
    PetoronMind& mind
) {
    for (const auto& fact : store.facts()) {
        mind.observe(fact);
    }
}

}
