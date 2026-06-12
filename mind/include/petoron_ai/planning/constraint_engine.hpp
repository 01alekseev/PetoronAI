/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct Constraint {
    std::string condition;
    std::string blocked_strategy;
};

struct ConstraintDecision {
    bool allowed = true;
    std::string reason;
};

ConstraintDecision evaluate_constraints(
    const std::vector<std::string>& world_facts,
    const std::vector<Constraint>& constraints,
    const std::string& strategy
);

}
