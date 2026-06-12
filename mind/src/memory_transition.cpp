/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory_transition.hpp"

namespace petoron_ai {

MemoryTransition apply_observation(
    const MemoryGraph& old_graph,
    const std::string& observation
) {
    MemoryGraph new_graph = old_graph;

    MemoryNode node;
    node.type = "observation";
    node.payload = observation;

    new_graph.nodes.push_back(node);

    MemoryTransition transition;
    transition.old_root = commit_memory_graph(old_graph);
    transition.new_root = commit_memory_graph(new_graph);
    transition.new_node = node;
    transition.observation = observation;

    return transition;
}

bool verify_memory_transition(
    const MemoryGraph& old_graph,
    const MemoryTransition& transition
) {
    if (transition.old_root != commit_memory_graph(old_graph)) {
        return false;
    }

    MemoryGraph new_graph = old_graph;
    new_graph.nodes.push_back(transition.new_node);

    if (transition.new_node.type != "observation") {
        return false;
    }

    if (transition.new_node.payload != transition.observation) {
        return false;
    }

    return transition.new_root == commit_memory_graph(new_graph);
}

}
