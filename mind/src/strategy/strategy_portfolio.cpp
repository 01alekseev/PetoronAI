/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_portfolio.hpp"

namespace petoron_ai {

StrategyPortfolio build_strategy_portfolio(
    const std::vector<RankedUtility>& ranked
) {
    StrategyPortfolio portfolio;

    if (ranked.empty()) {
        return portfolio;
    }

    portfolio.primary = ranked.front();

    for (std::size_t i = 1; i < ranked.size(); ++i) {
        if (i <= 2) {
            portfolio.support.push_back(ranked[i]);
        } else {
            portfolio.reserve.push_back(ranked[i]);
        }
    }

    return portfolio;
}

}
