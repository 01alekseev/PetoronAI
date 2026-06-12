/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"
#include "petoron_ai/strategy/strategy_artifact.hpp"

namespace petoron_ai {

struct StrategyExperience {
    MemoryDigest strategy_id{};
    int success_count = 0;
    int failure_count = 0;
    int reward_total = 0;
    MemoryDigest id{};
};

StrategyExperience make_strategy_experience(
    const StrategyArtifact& strategy,
    bool success,
    int reward
);

StrategyExperience merge_strategy_experience(
    const StrategyExperience& a,
    const StrategyExperience& b
);

int strategy_success_rate(
    const StrategyExperience& experience
);

}
