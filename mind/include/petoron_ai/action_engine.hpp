/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/goal_engine.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct ActionResult {
    std::string action;
    bool success;
    std::string outcome;
};

std::vector<ActionResult> execute_plan(
    const Plan& plan
);

}
