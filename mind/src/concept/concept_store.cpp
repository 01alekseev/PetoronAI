/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/concept/concept_store.hpp"

namespace petoron_ai {

bool add_concept(
    ConceptStore& store,
    const ConceptArtifact& artifact
) {
    for (const auto& item : store.concepts) {
        if (item.id == artifact.id) {
            return false;
        }
    }

    store.concepts.push_back(artifact);
    return true;
}

const ConceptArtifact* find_concept(
    const ConceptStore& store,
    const std::string& name
) {
    for (const auto& item : store.concepts) {
        if (item.name == name) {
            return &item;
        }
    }

    return nullptr;
}

}
