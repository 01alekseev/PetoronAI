/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/policy/policy_engine.hpp"

namespace petoron_ai {

std::vector<StrategyScore> filter_strategies(
    const Policy& policy,
    const std::vector<StrategyScore>& scores
);

}
