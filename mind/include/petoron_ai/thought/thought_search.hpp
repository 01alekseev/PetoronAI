/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/thought/thought_store.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

std::vector<ThoughtArtifact> find_thoughts_by_goal(
    const ThoughtStore& store,
    const std::string& source_goal
);

const ThoughtArtifact* best_thought_for_goal(
    const ThoughtStore& store,
    const std::string& source_goal
);

}
