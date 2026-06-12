/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"
#include "petoron_ai/thought/thought_graph.hpp"

#include <string>

namespace petoron_ai {

struct StrategyArtifact {
    std::string goal;
    ThoughtPath path;
    std::string action;
    int score = 0;
    MemoryDigest id{};
};

StrategyArtifact make_strategy_artifact(
    const std::string& goal,
    const ThoughtPath& path,
    const std::string& action
);

}
