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

struct MetaReasoningArtifact {
    std::string goal;
    std::string selected_action;
    int strategy_score = 0;
    std::string explanation;
    int confidence = 0;
    MemoryDigest id{};
};

MetaReasoningArtifact make_meta_reasoning_artifact(
    const StrategyArtifact& strategy
);

}
