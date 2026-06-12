/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/policy/policy_engine.hpp"

namespace petoron_ai {

static bool contains(
    const std::vector<std::string>& items,
    const std::string& value
) {
    for (const auto& item : items) {
        if (item == value) {
            return true;
        }
    }

    return false;
}

Policy build_policy(
    const std::vector<StrategyScore>& scores
) {
    Policy policy;

    for (const auto& score : scores) {
        if (score.score > 0) {
            if (!contains(policy.allowed, score.strategy)) {
                policy.allowed.push_back(score.strategy);
            }

            continue;
        }

        if (score.score < 0) {
            if (!contains(policy.forbidden, score.strategy)) {
                policy.forbidden.push_back(score.strategy);
            }

            continue;
        }
    }

    return policy;
}

bool policy_allows(
    const Policy& policy,
    const std::string& strategy
) {
    return contains(policy.allowed, strategy);
}

bool policy_forbids(
    const Policy& policy,
    const std::string& strategy
) {
    return contains(policy.forbidden, strategy);
}

}
