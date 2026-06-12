/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/knowledge/knowledge_store.hpp"

#include <string>

namespace petoron_ai {

bool write_knowledge_file(
    const std::string& path,
    const KnowledgeStore& store
);

bool read_knowledge_file(
    const std::string& path,
    KnowledgeStore& store
);

}
