/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_reinforcement.hpp"

namespace petoron_ai {

ReinforcedStrategy reinforce_strategy(
    const StrategyScore& score,
    const StrategyOutcome& outcome
) {
    ReinforcedStrategy result;
    result.strategy = score.strategy;
    result.old_score = score.score;
    result.new_score = score.score;

    if (score.strategy != outcome.strategy) {
        return result;
    }

    if (outcome.success) {
        result.new_score += outcome.reward;
    } else {
        result.new_score -= outcome.reward;
    }

    return result;
}

}
