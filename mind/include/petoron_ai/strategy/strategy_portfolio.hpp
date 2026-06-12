/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/utility_ranking.hpp"

#include <vector>

namespace petoron_ai {

struct StrategyPortfolio {
    RankedUtility primary;
    std::vector<RankedUtility> support;
    std::vector<RankedUtility> reserve;
};

StrategyPortfolio build_strategy_portfolio(
    const std::vector<RankedUtility>& ranked
);

}
