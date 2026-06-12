/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_artifact.hpp"

namespace petoron_ai {

ThoughtArtifact make_thought_artifact(
    const std::string& thought,
    const std::string& reason,
    const std::string& source_goal,
    int confidence
) {
    MemoryGraph graph;

    MemoryNode thought_node;
    thought_node.type = "thought";
    thought_node.payload = thought;
    graph.nodes.push_back(thought_node);

    MemoryNode reason_node;
    reason_node.type = "reason";
    reason_node.payload = reason;
    graph.nodes.push_back(reason_node);

    MemoryNode goal_node;
    goal_node.type = "source_goal";
    goal_node.payload = source_goal;
    graph.nodes.push_back(goal_node);

    MemoryNode confidence_node;
    confidence_node.type = "confidence";
    confidence_node.payload = std::to_string(confidence);
    graph.nodes.push_back(confidence_node);

    ThoughtArtifact artifact;
    artifact.thought = thought;
    artifact.reason = reason;
    artifact.source_goal = source_goal;
    artifact.confidence = confidence;
    artifact.id = commit_memory_graph(graph);

    return artifact;
}

}
