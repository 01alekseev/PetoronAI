/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_store.hpp"

namespace petoron_ai {

bool add_strategy(
    StrategyStore& store,
    const StrategyArtifact& strategy
) {
    for (const auto& item : store.strategies) {
        if (item.id == strategy.id) {
            return false;
        }
    }

    store.strategies.push_back(strategy);
    return true;
}

const StrategyArtifact* best_strategy_for_goal(
    const StrategyStore& store,
    const std::string& goal
) {
    const StrategyArtifact* best = nullptr;

    for (const auto& item : store.strategies) {
        if (item.goal != goal) {
            continue;
        }

        if (best == nullptr || item.score > best->score) {
            best = &item;
        }
    }

    return best;
}

}
