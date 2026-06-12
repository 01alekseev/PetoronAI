/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_controller.hpp"

namespace petoron_ai {

struct ExecutiveTickResult {
    bool planning = false;
    bool execution = false;
    bool learning = false;
};

ExecutiveTickResult execute_mind_tick(
    ExecutiveState state
);

}
