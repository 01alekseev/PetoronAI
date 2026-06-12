/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/agent_cycle.hpp"

#include <cstddef>

namespace petoron_ai {

struct AgentCycleTrace {
    MemoryDigest input_id;
    MemoryDigest kb_id;
    MemoryDigest start_root;
    MemoryDigest final_root;
    MemoryDigest plan_commitment;
    MemoryDigest actions_commitment;
    MemoryDigest feedback_commitment;
    std::string goal_name;
    std::size_t feedback_count;
};

AgentCycleTrace build_agent_cycle_trace(
    const MemoryDigest& input_id,
    const MemoryDigest& kb_id,
    const MemoryDigest& start_root,
    const Goal& goal,
    const AgentCycleResult& result
);

bool verify_agent_cycle_trace(
    const MemoryDigest& input_id,
    const MemoryDigest& kb_id,
    const MemoryDigest& start_root,
    const Goal& goal,
    const AgentCycleResult& result,
    const AgentCycleTrace& trace
);

}
