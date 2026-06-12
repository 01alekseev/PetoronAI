/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_planner.hpp"

namespace petoron_ai {

static const StrategyExperience* find_experience(
    const std::vector<StrategyExperience>& experiences,
    const MemoryDigest& strategy_id
) {
    for (const auto& item : experiences) {
        if (item.strategy_id == strategy_id) {
            return &item;
        }
    }

    return nullptr;
}

StrategyPlan plan_strategy(
    const StrategyStore& strategies,
    const std::vector<StrategyExperience>& experiences,
    const std::string& goal
) {
    StrategyPlan plan;
    plan.goal = goal;

    int best_rank = 0;

    for (const auto& strategy : strategies.strategies) {
        if (strategy.goal != goal) {
            continue;
        }

        int success_rate = 0;
        int reward = 0;

        const auto* experience =
            find_experience(
                experiences,
                strategy.id
            );

        if (experience != nullptr) {
            success_rate = strategy_success_rate(*experience);
            reward = experience->reward_total;
        }

        const int rank =
            strategy.score + success_rate + reward;

        if (!plan.found || rank > best_rank) {
            plan.selected_strategy = strategy;
            plan.expected_score = strategy.score;
            plan.success_rate = success_rate;
            plan.found = true;
            best_rank = rank;
        }
    }

    return plan;
}

}
