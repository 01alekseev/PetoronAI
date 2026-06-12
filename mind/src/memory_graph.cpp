/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory_graph.hpp"

#include <vector>

namespace petoron_ai {

MemoryDigest commit_memory_graph(const MemoryGraph& graph) {
    std::vector<std::uint8_t> bytes;

    for (const auto& node : graph.nodes) {
        const auto digest = commit_memory_node(node);
        bytes.insert(bytes.end(), digest.begin(), digest.end());
    }

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
