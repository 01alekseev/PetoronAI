/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/policy/policy_action_filter.hpp"
#include "petoron_ai/planning/constraint_engine.hpp"

namespace petoron_ai {

struct DecisionResult {
    std::string selected_strategy;
    bool allowed = false;
};

DecisionResult run_decision_pipeline(
    const Policy& policy,
    const std::vector<StrategyScore>& strategies,
    const std::vector<std::string>& world_facts,
    const std::vector<Constraint>& constraints
);

}
