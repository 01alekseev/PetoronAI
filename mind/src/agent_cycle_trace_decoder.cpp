/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/agent_cycle_trace_decoder.hpp"

namespace petoron_ai {

static bool read_digest(
    const std::vector<std::uint8_t>& bytes,
    std::size_t& offset,
    MemoryDigest& digest
) {
    if (bytes.size() - offset < digest.size()) {
        return false;
    }

    for (std::size_t i = 0; i < digest.size(); ++i) {
        digest[i] = bytes[offset + i];
    }

    offset += digest.size();
    return true;
}

static bool read_u64(
    const std::vector<std::uint8_t>& bytes,
    std::size_t& offset,
    std::uint64_t& value
) {
    if (bytes.size() - offset < 8) {
        return false;
    }

    value = 0;

    for (int i = 0; i < 8; ++i) {
        value |=
            static_cast<std::uint64_t>(bytes[offset + i])
            << (i * 8);
    }

    offset += 8;
    return true;
}

static bool read_string(
    const std::vector<std::uint8_t>& bytes,
    std::size_t& offset,
    std::string& value
) {
    std::uint64_t size = 0;

    if (!read_u64(bytes, offset, size)) {
        return false;
    }

    if (size > bytes.size() - offset) {
        return false;
    }

    value.assign(
        reinterpret_cast<const char*>(bytes.data() + offset),
        static_cast<std::size_t>(size)
    );

    offset += static_cast<std::size_t>(size);
    return true;
}

bool decode_agent_cycle_trace(
    const std::vector<std::uint8_t>& bytes,
    AgentCycleTrace& trace
) {
    std::size_t offset = 0;

    if (!read_digest(bytes, offset, trace.input_id)) {
        return false;
    }

    if (!read_digest(bytes, offset, trace.kb_id)) {
        return false;
    }

    if (!read_digest(bytes, offset, trace.start_root)) {
        return false;
    }

    if (!read_digest(bytes, offset, trace.final_root)) {
        return false;
    }

    if (!read_digest(bytes, offset, trace.plan_commitment)) {
        return false;
    }

    if (!read_digest(bytes, offset, trace.actions_commitment)) {
        return false;
    }

    if (!read_digest(bytes, offset, trace.feedback_commitment)) {
        return false;
    }

    if (!read_string(bytes, offset, trace.goal_name)) {
        return false;
    }

    std::uint64_t feedback_count = 0;

    if (!read_u64(bytes, offset, feedback_count)) {
        return false;
    }

    trace.feedback_count =
        static_cast<std::size_t>(feedback_count);

    return offset == bytes.size();
}

}
