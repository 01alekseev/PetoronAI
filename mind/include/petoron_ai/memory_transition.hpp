/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"

#include <string>

namespace petoron_ai {

struct MemoryTransition {
    MemoryDigest old_root;
    MemoryDigest new_root;
    MemoryNode new_node;
    std::string observation;
};

MemoryTransition apply_observation(
    const MemoryGraph& old_graph,
    const std::string& observation
);

bool verify_memory_transition(
    const MemoryGraph& old_graph,
    const MemoryTransition& transition
);

}
