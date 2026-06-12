/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_store.hpp"

namespace petoron_ai {

bool add_thought(
    ThoughtStore& store,
    const ThoughtArtifact& artifact
) {
    for (const auto& item : store.thoughts) {
        if (item.id == artifact.id) {
            return false;
        }
    }

    store.thoughts.push_back(artifact);
    return true;
}

}
