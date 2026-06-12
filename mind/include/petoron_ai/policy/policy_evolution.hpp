/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/strategy_reinforcement.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct PolicyEntry {
    std::string strategy;
    int trust = 0;
};

struct EvolvingPolicy {
    std::vector<PolicyEntry> entries;
};

bool update_policy(
    EvolvingPolicy& policy,
    const ReinforcedStrategy& result
);

const PolicyEntry* find_policy_entry(
    const EvolvingPolicy& policy,
    const std::string& strategy
);

}
