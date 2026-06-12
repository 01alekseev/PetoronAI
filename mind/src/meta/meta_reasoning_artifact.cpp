/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/meta/meta_reasoning_artifact.hpp"

namespace petoron_ai {

MetaReasoningArtifact make_meta_reasoning_artifact(
    const StrategyArtifact& strategy
) {
    MetaReasoningArtifact artifact;
    artifact.goal = strategy.goal;
    artifact.selected_action = strategy.action;
    artifact.strategy_score = strategy.score;
    artifact.confidence = strategy.score;

    if (strategy.path.found) {
        artifact.explanation =
            "selected strategy has verified thought path";
    } else {
        artifact.explanation =
            "selected strategy has no verified thought path";
    }

    MemoryGraph graph;

    MemoryNode goal_node;
    goal_node.type = "meta_goal";
    goal_node.payload = artifact.goal;
    graph.nodes.push_back(goal_node);

    MemoryNode action_node;
    action_node.type = "meta_selected_action";
    action_node.payload = artifact.selected_action;
    graph.nodes.push_back(action_node);

    MemoryNode score_node;
    score_node.type = "meta_strategy_score";
    score_node.payload = std::to_string(artifact.strategy_score);
    graph.nodes.push_back(score_node);

    MemoryNode confidence_node;
    confidence_node.type = "meta_confidence";
    confidence_node.payload = std::to_string(artifact.confidence);
    graph.nodes.push_back(confidence_node);

    MemoryNode explanation_node;
    explanation_node.type = "meta_explanation";
    explanation_node.payload = artifact.explanation;
    graph.nodes.push_back(explanation_node);

    artifact.id = commit_memory_graph(graph);

    return artifact;
}

}
