/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/concept/concept_artifact.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct ConceptStore {
    std::vector<ConceptArtifact> concepts;
};

bool add_concept(
    ConceptStore& store,
    const ConceptArtifact& artifact
);

const ConceptArtifact* find_concept(
    const ConceptStore& store,
    const std::string& name
);

}
