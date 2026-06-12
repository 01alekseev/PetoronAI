/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/strategy_experience.hpp"
#include "petoron_ai/strategy/strategy_store.hpp"

#include <vector>

namespace petoron_ai {

struct StrategyPlan {
    std::string goal;
    StrategyArtifact selected_strategy;
    int expected_score = 0;
    int success_rate = 0;
    bool found = false;
};

StrategyPlan plan_strategy(
    const StrategyStore& strategies,
    const std::vector<StrategyExperience>& experiences,
    const std::string& goal
);

}
