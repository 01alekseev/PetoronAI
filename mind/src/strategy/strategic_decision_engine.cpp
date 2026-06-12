/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategic_decision_engine.hpp"

namespace petoron_ai {

StrategicDecision make_strategic_decision(
    const StrategyPortfolio& portfolio
) {
    StrategicDecision result;

    if (portfolio.primary.utility <= 0) {
        return result;
    }

    result.executable = true;
    result.utility = portfolio.primary.utility;
    result.decision = "execute_primary_strategy";

    return result;
}

}
