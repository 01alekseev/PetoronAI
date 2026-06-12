/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reflection/reflection_artifact.hpp"

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

ReflectionArtifact make_reflection_artifact(
    const StrategyArtifact& strategy,
    bool success,
    int reward
) {
    ReflectionArtifact artifact;
    artifact.strategy_id = strategy.id;
    artifact.goal = strategy.goal;
    artifact.action = strategy.action;
    artifact.success = success;
    artifact.reward = reward;

    if (success) {
        artifact.lesson = "strategy should be reinforced";
    } else {
        artifact.lesson = "strategy should be reconsidered";
    }

    MemoryGraph graph;

    MemoryNode strategy_node;
    strategy_node.type = "reflection_strategy";
    strategy_node.payload = digest_to_text(artifact.strategy_id);
    graph.nodes.push_back(strategy_node);

    MemoryNode goal_node;
    goal_node.type = "reflection_goal";
    goal_node.payload = artifact.goal;
    graph.nodes.push_back(goal_node);

    MemoryNode action_node;
    action_node.type = "reflection_action";
    action_node.payload = artifact.action;
    graph.nodes.push_back(action_node);

    MemoryNode success_node;
    success_node.type = "reflection_success";
    success_node.payload = artifact.success ? "1" : "0";
    graph.nodes.push_back(success_node);

    MemoryNode reward_node;
    reward_node.type = "reflection_reward";
    reward_node.payload = std::to_string(artifact.reward);
    graph.nodes.push_back(reward_node);

    MemoryNode lesson_node;
    lesson_node.type = "reflection_lesson";
    lesson_node.payload = artifact.lesson;
    graph.nodes.push_back(lesson_node);

    artifact.id = commit_memory_graph(graph);

    return artifact;
}

}
