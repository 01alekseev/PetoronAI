/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/knowledge/knowledge_relation.hpp"
#include "petoron_ai/memory_graph.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

class KnowledgeStore {
public:
    bool add_fact(
        const std::string& payload
    );

    bool has_fact(
        const std::string& payload
    ) const;

    bool add_relation(
        const KnowledgeRelation& relation
    );

    bool has_relation(
        const KnowledgeRelation& relation
    ) const;

    std::vector<std::string> facts() const;

    std::vector<KnowledgeRelation> relations_from(
        const std::string& from
    ) const;

    std::vector<KnowledgeRelation> relations_to(
        const std::string& to
    ) const;

    const MemoryGraph& graph() const;

    MemoryDigest root() const;

private:
    MemoryGraph graph_;
};

}
