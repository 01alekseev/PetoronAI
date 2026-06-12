/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_controller.hpp"

namespace petoron_ai {

ExecutiveState next_executive_state(
    ExecutiveState current,
    bool planning_complete,
    bool execution_complete,
    bool execution_failed
);

}
