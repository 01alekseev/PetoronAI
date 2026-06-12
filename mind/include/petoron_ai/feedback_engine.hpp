/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/action_engine.hpp"

namespace petoron_ai {

std::vector<MemoryTransition> learn_from_actions(
    PetoronMind& mind,
    const std::vector<ActionResult>& results
);

}
