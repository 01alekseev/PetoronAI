/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/agent_cycle_trace_codec.hpp"

namespace petoron_ai {

static void append_digest(
    std::vector<std::uint8_t>& out,
    const MemoryDigest& digest
) {
    out.insert(out.end(), digest.begin(), digest.end());
}

static void append_string(
    std::vector<std::uint8_t>& out,
    const std::string& value
) {
    const auto size =
        static_cast<std::uint64_t>(value.size());

    for (int i = 0; i < 8; ++i) {
        out.push_back(
            static_cast<std::uint8_t>(
                (size >> (i * 8)) & 0xff
            )
        );
    }

    out.insert(out.end(), value.begin(), value.end());
}

static void append_size(
    std::vector<std::uint8_t>& out,
    std::size_t value
) {
    const auto size =
        static_cast<std::uint64_t>(value);

    for (int i = 0; i < 8; ++i) {
        out.push_back(
            static_cast<std::uint8_t>(
                (size >> (i * 8)) & 0xff
            )
        );
    }
}

std::vector<std::uint8_t> encode_agent_cycle_trace(
    const AgentCycleTrace& trace
) {
    std::vector<std::uint8_t> out;

    append_digest(out, trace.input_id);
    append_digest(out, trace.kb_id);
    append_digest(out, trace.start_root);
    append_digest(out, trace.final_root);
    append_digest(out, trace.plan_commitment);
    append_digest(out, trace.actions_commitment);
    append_digest(out, trace.feedback_commitment);
    append_string(out, trace.goal_name);
    append_size(out, trace.feedback_count);

    return out;
}

MemoryDigest commit_agent_cycle_trace(
    const AgentCycleTrace& trace
) {
    const auto bytes = encode_agent_cycle_trace(trace);
    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
