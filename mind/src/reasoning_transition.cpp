/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning_transition.hpp"

namespace petoron_ai {

ReasoningTransition apply_reasoning_transition(
    const MemoryGraph& old_graph,
    const MemoryNode& left,
    const MemoryNode& right,
    const ReasoningRule& rule
) {
    const auto result =
        apply_reasoning_rule(left, right, rule);

    MemoryGraph new_graph = old_graph;

    if (result.valid) {
        new_graph.nodes.push_back(result.conclusion);
    }

    ReasoningTransition transition;
    transition.old_root = commit_memory_graph(old_graph);
    transition.new_root = commit_memory_graph(new_graph);
    transition.rule = rule;
    transition.left = left;
    transition.right = right;
    transition.conclusion = result.conclusion;

    return transition;
}

bool verify_reasoning_transition(
    const MemoryGraph& old_graph,
    const ReasoningTransition& transition
) {
    if (transition.old_root != commit_memory_graph(old_graph)) {
        return false;
    }

    const auto result =
        apply_reasoning_rule(
            transition.left,
            transition.right,
            transition.rule
        );

    if (!result.valid) {
        return false;
    }

    if (result.conclusion.type != transition.conclusion.type) {
        return false;
    }

    if (result.conclusion.payload != transition.conclusion.payload) {
        return false;
    }

    if (result.conclusion.links != transition.conclusion.links) {
        return false;
    }

    MemoryGraph new_graph = old_graph;
    new_graph.nodes.push_back(transition.conclusion);

    return transition.new_root == commit_memory_graph(new_graph);
}

}
