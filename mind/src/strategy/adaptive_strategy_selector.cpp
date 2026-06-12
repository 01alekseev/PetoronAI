/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/adaptive_strategy_selector.hpp"

namespace petoron_ai {

AdaptiveStrategy select_strategy(
    const std::vector<AdaptiveStrategy>& strategies,
    int budget
) {
    AdaptiveStrategy best;
    bool found = false;

    for (const auto& strategy : strategies) {
        if (strategy.cost > budget) {
            continue;
        }

        if (!found || strategy.score > best.score) {
            best = strategy;
            found = true;
        }
    }

    return best;
}

}
