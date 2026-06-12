/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "proof/commitment/petoron_zk_commitment.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

using MemoryDigest =
    petoron::zk::PetoronZkCommitment::Digest;

struct MemoryNode {
    std::string type;
    std::string payload;
    std::vector<MemoryDigest> links;
};

MemoryDigest commit_memory_node(const MemoryNode& node);

}
