/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/knowledge/knowledge_store.hpp"

namespace petoron_ai {

std::vector<MemoryNode> knowledge_feedback_delta(
    const KnowledgeStore& old_store,
    const KnowledgeStore& new_store
);

MemoryDigest commit_knowledge_feedback_delta(
    const KnowledgeStore& old_store,
    const KnowledgeStore& new_store
);

}
