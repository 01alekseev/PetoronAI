/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/world/world_goal_impact.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct StrategyScore {
    std::string strategy;
    int score = 0;
};

std::vector<StrategyScore> score_strategies(
    const std::vector<GoalImpact>& impacts
);

StrategyScore select_best_strategy(
    const std::vector<StrategyScore>& scores
);

}
