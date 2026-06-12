/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/concept/concept_artifact.hpp"

namespace petoron_ai {

ConceptArtifact make_concept_artifact(
    const std::string& name,
    const std::vector<std::string>& parents,
    int confidence,
    int generation
) {
    MemoryGraph graph;

    MemoryNode name_node;
    name_node.type = "concept_name";
    name_node.payload = name;
    graph.nodes.push_back(name_node);

    for (const auto& parent : parents) {
        MemoryNode parent_node;
        parent_node.type = "concept_parent";
        parent_node.payload = parent;
        graph.nodes.push_back(parent_node);
    }

    MemoryNode confidence_node;
    confidence_node.type = "concept_confidence";
    confidence_node.payload = std::to_string(confidence);
    graph.nodes.push_back(confidence_node);

    MemoryNode generation_node;
    generation_node.type = "concept_generation";
    generation_node.payload = std::to_string(generation);
    graph.nodes.push_back(generation_node);

    ConceptArtifact artifact;
    artifact.name = name;
    artifact.parents = parents;
    artifact.confidence = confidence;
    artifact.generation = generation;
    artifact.id = commit_memory_graph(graph);

    return artifact;
}

}
