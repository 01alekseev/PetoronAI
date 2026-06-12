/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct AdaptiveStrategy {
    std::string name;
    int score = 0;
    int cost = 0;
};

AdaptiveStrategy select_strategy(
    const std::vector<AdaptiveStrategy>& strategies,
    int budget
);

}
