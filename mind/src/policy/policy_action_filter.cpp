/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/policy/policy_action_filter.hpp"

namespace petoron_ai {

std::vector<StrategyScore> filter_strategies(
    const Policy& policy,
    const std::vector<StrategyScore>& scores
) {
    std::vector<StrategyScore> out;

    for (const auto& score : scores) {
        if (policy_forbids(policy, score.strategy)) {
            continue;
        }

        out.push_back(score);
    }

    return out;
}

}
