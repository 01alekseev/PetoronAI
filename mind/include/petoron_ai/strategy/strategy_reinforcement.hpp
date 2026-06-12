/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/strategy_scoring.hpp"

#include <string>

namespace petoron_ai {

struct StrategyOutcome {
    std::string strategy;
    bool success = false;
    int reward = 0;
};

struct ReinforcedStrategy {
    std::string strategy;
    int old_score = 0;
    int new_score = 0;
};

ReinforcedStrategy reinforce_strategy(
    const StrategyScore& score,
    const StrategyOutcome& outcome
);

}
