/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/knowledge/knowledge_store.hpp"
#include "petoron_ai/petoron_mind.hpp"

namespace petoron_ai {

void load_knowledge_into_mind(
    const KnowledgeStore& store,
    PetoronMind& mind
);

}
