/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/strategy_store.hpp"

namespace petoron_ai {

StrategyArtifact evolve_strategy(
    const StrategyArtifact& a,
    const StrategyArtifact& b,
    const std::string& evolved_goal,
    const std::string& evolved_action
);

}
