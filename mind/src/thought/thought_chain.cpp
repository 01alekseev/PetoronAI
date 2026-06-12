/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_chain.hpp"

#include "petoron_ai/memory_graph.hpp"

namespace petoron_ai {

ThoughtChain make_thought_chain(
    const std::vector<ThoughtArtifact>& steps
) {
    MemoryGraph graph;

    for (const auto& step : steps) {
        MemoryNode node;
        node.type = "thought_step";
        node.payload =
            step.source_goal + "|" +
            step.thought + "|" +
            step.reason + "|" +
            std::to_string(step.confidence);

        graph.nodes.push_back(node);
    }

    ThoughtChain chain;
    chain.steps = steps;
    chain.id = commit_memory_graph(graph);

    return chain;
}

int thought_chain_confidence(
    const ThoughtChain& chain
) {
    if (chain.steps.empty()) {
        return 0;
    }

    int total = 0;

    for (const auto& step : chain.steps) {
        total += step.confidence;
    }

    return total / static_cast<int>(chain.steps.size());
}

}
