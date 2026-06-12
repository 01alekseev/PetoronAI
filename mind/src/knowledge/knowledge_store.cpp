/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_store.hpp"

namespace petoron_ai {

static bool parse_relation_payload(
    const std::string& payload,
    KnowledgeRelation& relation
) {
    const auto colon = payload.find(':');
    const auto arrow = payload.find("->");

    if (colon == std::string::npos) {
        return false;
    }

    if (arrow == std::string::npos) {
        return false;
    }

    if (colon >= arrow) {
        return false;
    }

    relation.type = payload.substr(0, colon);
    relation.from = payload.substr(colon + 1, arrow - colon - 1);
    relation.to = payload.substr(arrow + 2);

    return !relation.type.empty() &&
        !relation.from.empty() &&
        !relation.to.empty();
}

bool KnowledgeStore::add_fact(
    const std::string& payload
) {
    if (payload.empty()) {
        return false;
    }

    if (has_fact(payload)) {
        return false;
    }

    MemoryNode node;
    node.type = "fact";
    node.payload = payload;

    graph_.nodes.push_back(node);
    return true;
}

bool KnowledgeStore::has_fact(
    const std::string& payload
) const {
    for (const auto& node : graph_.nodes) {
        if (
            node.type == "fact" &&
            node.payload == payload
        ) {
            return true;
        }
    }

    return false;
}

bool KnowledgeStore::add_relation(
    const KnowledgeRelation& relation
) {
    if (
        relation.type.empty() ||
        relation.from.empty() ||
        relation.to.empty()
    ) {
        return false;
    }

    if (!has_fact(relation.from)) {
        return false;
    }

    if (!has_fact(relation.to)) {
        return false;
    }

    if (has_relation(relation)) {
        return false;
    }

    graph_.nodes.push_back(
        make_relation_node(relation)
    );

    return true;
}

bool KnowledgeStore::has_relation(
    const KnowledgeRelation& relation
) const {
    const auto relation_node =
        make_relation_node(relation);

    for (const auto& node : graph_.nodes) {
        if (
            node.type == relation_node.type &&
            node.payload == relation_node.payload
        ) {
            return true;
        }
    }

    return false;
}

std::vector<std::string> KnowledgeStore::facts() const {
    std::vector<std::string> out;

    for (const auto& node : graph_.nodes) {
        if (node.type == "fact") {
            out.push_back(node.payload);
        }
    }

    return out;
}

std::vector<KnowledgeRelation> KnowledgeStore::relations_from(
    const std::string& from
) const {
    std::vector<KnowledgeRelation> out;

    for (const auto& node : graph_.nodes) {
        if (node.type != "relation") {
            continue;
        }

        KnowledgeRelation relation;

        if (!parse_relation_payload(node.payload, relation)) {
            continue;
        }

        if (relation.from == from) {
            out.push_back(relation);
        }
    }

    return out;
}

std::vector<KnowledgeRelation> KnowledgeStore::relations_to(
    const std::string& to
) const {
    std::vector<KnowledgeRelation> out;

    for (const auto& node : graph_.nodes) {
        if (node.type != "relation") {
            continue;
        }

        KnowledgeRelation relation;

        if (!parse_relation_payload(node.payload, relation)) {
            continue;
        }

        if (relation.to == to) {
            out.push_back(relation);
        }
    }

    return out;
}

const MemoryGraph& KnowledgeStore::graph() const {
    return graph_;
}

MemoryDigest KnowledgeStore::root() const {
    return commit_memory_graph(graph_);
}

}
