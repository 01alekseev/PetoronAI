/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_relation.hpp"

namespace petoron_ai {

MemoryNode make_relation_node(
    const KnowledgeRelation& relation
) {
    MemoryNode node;
    node.type = "relation";
    node.payload =
        relation.type + ":" + relation.from + "->" + relation.to;
    return node;
}

}
