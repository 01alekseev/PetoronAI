/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/thought/thought_artifact.hpp"

#include <vector>

namespace petoron_ai {

struct ThoughtChain {
    std::vector<ThoughtArtifact> steps;
    MemoryDigest id{};
};

ThoughtChain make_thought_chain(
    const std::vector<ThoughtArtifact>& steps
);

int thought_chain_confidence(
    const ThoughtChain& chain
);

}
