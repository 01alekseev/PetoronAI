/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning_trace_codec.hpp"

namespace petoron_ai {

static void append_digest(
    std::vector<std::uint8_t>& out,
    const MemoryDigest& digest
) {
    out.insert(
        out.end(),
        digest.begin(),
        digest.end()
    );
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

    out.insert(
        out.end(),
        value.begin(),
        value.end()
    );
}

std::vector<std::uint8_t> encode_reasoning_trace(
    const ReasoningTrace& trace
) {
    std::vector<std::uint8_t> out;

    append_digest(out, trace.old_root);
    append_digest(out, trace.new_root);
    append_digest(out, trace.left_commitment);
    append_digest(out, trace.right_commitment);
    append_digest(out, trace.conclusion_commitment);
    append_string(out, trace.rule_name);

    return out;
}

MemoryDigest commit_reasoning_trace(
    const ReasoningTrace& trace
) {
    const auto bytes = encode_reasoning_trace(trace);
    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
