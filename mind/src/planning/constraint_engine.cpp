/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/constraint_engine.hpp"

namespace petoron_ai {

ConstraintDecision evaluate_constraints(
    const std::vector<std::string>& world_facts,
    const std::vector<Constraint>& constraints,
    const std::string& strategy
) {
    for (const auto& constraint : constraints) {
        if (constraint.blocked_strategy != strategy) {
            continue;
        }

        for (const auto& fact : world_facts) {
            if (fact == constraint.condition) {
                ConstraintDecision result;
                result.allowed = false;
                result.reason = constraint.condition;
                return result;
            }
        }
    }

    return ConstraintDecision{};
}

}
