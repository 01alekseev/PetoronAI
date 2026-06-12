/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/policy/policy_evolution.hpp"

namespace petoron_ai {

static PolicyEntry* find_mutable_policy_entry(
    EvolvingPolicy& policy,
    const std::string& strategy
) {
    for (auto& entry : policy.entries) {
        if (entry.strategy == strategy) {
            return &entry;
        }
    }

    return nullptr;
}

const PolicyEntry* find_policy_entry(
    const EvolvingPolicy& policy,
    const std::string& strategy
) {
    for (const auto& entry : policy.entries) {
        if (entry.strategy == strategy) {
            return &entry;
        }
    }

    return nullptr;
}

bool update_policy(
    EvolvingPolicy& policy,
    const ReinforcedStrategy& result
) {
    if (result.strategy.empty()) {
        return false;
    }

    int delta = 0;

    if (result.new_score > result.old_score) {
        delta = 1;
    } else if (result.new_score < result.old_score) {
        delta = -1;
    } else {
        return false;
    }

    auto* entry =
        find_mutable_policy_entry(
            policy,
            result.strategy
        );

    if (entry == nullptr) {
        PolicyEntry created;
        created.strategy = result.strategy;
        created.trust = delta;
        policy.entries.push_back(created);
        return true;
    }

    entry->trust += delta;
    return true;
}

}
