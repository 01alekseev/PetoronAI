/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_node.hpp"

#include <vector>

namespace petoron_ai {

struct MemoryGraph {
    std::vector<MemoryNode> nodes;
};

MemoryDigest commit_memory_graph(const MemoryGraph& graph);

}
