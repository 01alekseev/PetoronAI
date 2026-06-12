/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"

#include <string>

namespace petoron_ai {

struct ThoughtArtifact {
    std::string thought;
    std::string reason;
    std::string source_goal;
    int confidence = 0;
    MemoryDigest id{};
};

ThoughtArtifact make_thought_artifact(
    const std::string& thought,
    const std::string& reason,
    const std::string& source_goal,
    int confidence
);

}
