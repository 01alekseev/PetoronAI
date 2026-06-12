/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/strategy_portfolio.hpp"

#include <string>

namespace petoron_ai {

struct StrategicDecision {
    bool executable = false;
    int utility = 0;
    std::string decision;
};

StrategicDecision make_strategic_decision(
    const StrategyPortfolio& portfolio
);

}
