/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/thought/thought_artifact.hpp"

#include <vector>

namespace petoron_ai {

struct ThoughtEdge {
    MemoryDigest from{};
    MemoryDigest to{};
    int weight = 0;
};

struct ThoughtGraph {
    std::vector<ThoughtArtifact> nodes;
    std::vector<ThoughtEdge> edges;
    MemoryDigest id{};
};

ThoughtGraph make_thought_graph(
    const std::vector<ThoughtArtifact>& nodes,
    const std::vector<ThoughtEdge>& edges
);

bool has_thought_path(
    const ThoughtGraph& graph,
    const MemoryDigest& from,
    const MemoryDigest& to
);

}

namespace petoron_ai {

struct ThoughtPath {
    std::vector<MemoryDigest> nodes;
    int score = 0;
    bool found = false;
};

ThoughtPath best_thought_path(
    const ThoughtGraph& graph,
    const MemoryDigest& start
);

}
