/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_scoring.hpp"

namespace petoron_ai {

static std::string strategy_from_impact(
    const GoalImpact& impact
) {
    if (
        impact.positive &&
        impact.object == "shelter"
    ) {
        return "find shelter";
    }

    if (
        impact.positive &&
        impact.object == "distance"
    ) {
        return "keep distance";
    }

    if (
        !impact.positive &&
        impact.object == "danger"
    ) {
        return "walk into storm";
    }

    if (
        !impact.positive &&
        impact.object == "injury"
    ) {
        return "approach injury source";
    }

    return {};
}

std::vector<StrategyScore> score_strategies(
    const std::vector<GoalImpact>& impacts
) {
    std::vector<StrategyScore> scores;

    for (const auto& impact : impacts) {
        const auto strategy =
            strategy_from_impact(impact);

        if (strategy.empty()) {
            continue;
        }

        bool found = false;

        for (auto& score : scores) {
            if (score.strategy == strategy) {
                score.score += impact.impact_score;
                found = true;
                break;
            }
        }

        if (!found) {
            StrategyScore score;
            score.strategy = strategy;
            score.score = impact.impact_score;
            scores.push_back(score);
        }
    }

    return scores;
}

StrategyScore select_best_strategy(
    const std::vector<StrategyScore>& scores
) {
    StrategyScore best;

    if (scores.empty()) {
        return best;
    }

    best = scores.front();

    for (const auto& score : scores) {
        if (score.score > best.score) {
            best = score;
        }
    }

    return best;
}

}
