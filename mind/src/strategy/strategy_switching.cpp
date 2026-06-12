/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_switching.hpp"
#include "petoron_ai/strategy/strategy_portfolio.hpp"

namespace petoron_ai {

bool should_switch_strategy(
    int current_utility,
    int candidate_utility
) {
    return candidate_utility > current_utility;
}

RankedUtility select_replacement_strategy(
    const RankedUtility& current,
    const StrategyPortfolio& portfolio
) {
    if (
        !portfolio.support.empty() &&
        portfolio.support.front().utility > current.utility
    ) {
        return portfolio.support.front();
    }

    return current;
}

}
