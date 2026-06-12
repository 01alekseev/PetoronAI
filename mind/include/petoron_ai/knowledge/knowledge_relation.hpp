/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_node.hpp"

#include <string>

namespace petoron_ai {

struct KnowledgeRelation {
    std::string type;
    std::string from;
    std::string to;
};

MemoryNode make_relation_node(
    const KnowledgeRelation& relation
);

}
