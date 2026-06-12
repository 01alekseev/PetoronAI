/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"
#include "petoron_ai/strategy/strategy_artifact.hpp"

#include <string>

namespace petoron_ai {

struct ReflectionArtifact {
    MemoryDigest strategy_id{};
    std::string goal;
    std::string action;
    bool success = false;
    int reward = 0;
    std::string lesson;
    MemoryDigest id{};
};

ReflectionArtifact make_reflection_artifact(
    const StrategyArtifact& strategy,
    bool success,
    int reward
);

}
