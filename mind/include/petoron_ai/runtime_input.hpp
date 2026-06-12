/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/agent_cycle.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct RuntimeInput {
    std::vector<std::string> observations;
    std::vector<ReasoningRule> rules;
    Goal goal;
    std::vector<Goal> goal_candidates;
};

bool read_runtime_input(
    const std::string& path,
    RuntimeInput& input
);

}
