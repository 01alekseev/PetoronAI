/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct ConceptArtifact {
    std::string name;
    std::vector<std::string> parents;
    int confidence = 0;
    int generation = 0;
    MemoryDigest id{};
};

ConceptArtifact make_concept_artifact(
    const std::string& name,
    const std::vector<std::string>& parents,
    int confidence,
    int generation
);

}
