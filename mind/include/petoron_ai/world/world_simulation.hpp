/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct SimulatedFuture {
    std::vector<std::string> facts;
    int risk = 0;
};

SimulatedFuture simulate_world(
    const std::vector<std::string>& world_facts,
    const std::string& action
);

}
