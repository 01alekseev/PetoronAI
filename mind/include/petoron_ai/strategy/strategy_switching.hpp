/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/utility_ranking.hpp"
#include "petoron_ai/strategy/strategy_portfolio.hpp"

namespace petoron_ai {

bool should_switch_strategy(
    int current_utility,
    int candidate_utility
);

RankedUtility select_replacement_strategy(
    const RankedUtility& current,
    const StrategyPortfolio& portfolio
);

}
