/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/agent_cycle_trace_codec.hpp"

#include <cstddef>
#include <vector>

namespace petoron_ai {

bool decode_agent_cycle_trace(
    const std::vector<std::uint8_t>& bytes,
    AgentCycleTrace& trace
);

}
