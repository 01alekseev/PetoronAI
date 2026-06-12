/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_controller.hpp"

namespace petoron_ai {

struct ExecutiveCycle {
    bool planning = false;
    bool execution = false;
    bool learning = false;
};

ExecutiveCycle build_executive_cycle(
    ExecutiveState state
);

}
