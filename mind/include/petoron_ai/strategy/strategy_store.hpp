/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/strategy_artifact.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct StrategyStore {
    std::vector<StrategyArtifact> strategies;
};

bool add_strategy(
    StrategyStore& store,
    const StrategyArtifact& strategy
);

const StrategyArtifact* best_strategy_for_goal(
    const StrategyStore& store,
    const std::string& goal
);

}
