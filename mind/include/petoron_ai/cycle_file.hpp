/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/agent_cycle_trace_decoder.hpp"

#include <string>

namespace petoron_ai {

struct CycleFile {
    MemoryDigest cycle_id;
    MemoryDigest final_root;
    AgentCycleTrace trace;
};

bool write_cycle_file(
    const std::string& path,
    const AgentCycleTrace& trace
);

bool read_cycle_file(
    const std::string& path,
    CycleFile& file
);

bool verify_cycle_file(
    const CycleFile& file
);

}
