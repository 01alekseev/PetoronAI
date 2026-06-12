/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/thought/thought_artifact.hpp"

#include <vector>

namespace petoron_ai {

struct ThoughtStore {
    std::vector<ThoughtArtifact> thoughts;
};

bool add_thought(
    ThoughtStore& store,
    const ThoughtArtifact& artifact
);

}
