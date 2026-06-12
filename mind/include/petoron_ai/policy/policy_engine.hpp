/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/strategy_scoring.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct Policy {
    std::vector<std::string> allowed;
    std::vector<std::string> forbidden;
};

Policy build_policy(
    const std::vector<StrategyScore>& scores
);

bool policy_allows(
    const Policy& policy,
    const std::string& strategy
);

bool policy_forbids(
    const Policy& policy,
    const std::string& strategy
);

}
