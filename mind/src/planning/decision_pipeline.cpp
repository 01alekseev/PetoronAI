/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/decision_pipeline.hpp"

namespace petoron_ai {

DecisionResult run_decision_pipeline(
    const Policy& policy,
    const std::vector<StrategyScore>& strategies,
    const std::vector<std::string>& world_facts,
    const std::vector<Constraint>& constraints
) {
    DecisionResult result;

    const auto filtered =
        filter_strategies(
            policy,
            strategies
        );

    for (const auto& strategy : filtered) {
        const auto decision =
            evaluate_constraints(
                world_facts,
                constraints,
                strategy.strategy
            );

        if (!decision.allowed) {
            continue;
        }

        result.selected_strategy =
            strategy.strategy;

        result.allowed = true;
        return result;
    }

    return result;
}

}
