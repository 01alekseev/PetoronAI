/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_model.hpp"

namespace petoron_ai {

static MemoryDigest commit_world_model(
    const std::vector<WorldRelation>& relations
) {
    MemoryGraph graph;

    for (const auto& relation : relations) {
        MemoryNode node;
        node.type = "world_relation";
        node.payload =
            relation.subject + "|" +
            relation.relation + "|" +
            relation.object + "|" +
            std::to_string(relation.confidence);

        graph.nodes.push_back(node);
    }

    return commit_memory_graph(graph);
}

WorldModel make_world_model(
    const std::vector<WorldRelation>& relations
) {
    WorldModel model;
    model.relations = relations;
    model.id = commit_world_model(model.relations);
    return model;
}

bool add_world_relation(
    WorldModel& model,
    const WorldRelation& relation
) {
    for (const auto& item : model.relations) {
        if (
            item.subject == relation.subject &&
            item.relation == relation.relation &&
            item.object == relation.object
        ) {
            return false;
        }
    }

    model.relations.push_back(relation);
    model.id = commit_world_model(model.relations);
    return true;
}

std::vector<WorldRelation> find_world_relations(
    const WorldModel& model,
    const std::string& subject
) {
    std::vector<WorldRelation> out;

    for (const auto& item : model.relations) {
        if (item.subject == subject) {
            out.push_back(item);
        }
    }

    return out;
}

}
