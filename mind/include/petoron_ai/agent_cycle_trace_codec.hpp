/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/agent_cycle_trace.hpp"

#include <cstdint>
#include <vector>

namespace petoron_ai {

std::vector<std::uint8_t> encode_agent_cycle_trace(
    const AgentCycleTrace& trace
);

MemoryDigest commit_agent_cycle_trace(
    const AgentCycleTrace& trace
);

}
