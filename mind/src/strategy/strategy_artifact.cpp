/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_artifact.hpp"

#include <sstream>

namespace petoron_ai {

static std::string digest_to_text(
    const MemoryDigest& digest
) {
    std::ostringstream out;

    for (const auto byte : digest) {
        out << static_cast<int>(byte) << ",";
    }

    return out.str();
}

StrategyArtifact make_strategy_artifact(
    const std::string& goal,
    const ThoughtPath& path,
    const std::string& action
) {
    MemoryGraph graph;

    MemoryNode goal_node;
    goal_node.type = "strategy_goal";
    goal_node.payload = goal;
    graph.nodes.push_back(goal_node);

    MemoryNode action_node;
    action_node.type = "strategy_action";
    action_node.payload = action;
    graph.nodes.push_back(action_node);

    MemoryNode score_node;
    score_node.type = "strategy_score";
    score_node.payload = std::to_string(path.score);
    graph.nodes.push_back(score_node);

    MemoryNode found_node;
    found_node.type = "strategy_found";
    found_node.payload = path.found ? "1" : "0";
    graph.nodes.push_back(found_node);

    for (const auto& node : path.nodes) {
        MemoryNode path_node;
        path_node.type = "strategy_path_node";
        path_node.payload = digest_to_text(node);
        graph.nodes.push_back(path_node);
    }

    StrategyArtifact artifact;
    artifact.goal = goal;
    artifact.path = path;
    artifact.action = action;
    artifact.score = path.score;
    artifact.id = commit_memory_graph(graph);

    return artifact;
}

}
