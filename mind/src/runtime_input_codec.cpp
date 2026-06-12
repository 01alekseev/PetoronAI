/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime_input_codec.hpp"

namespace petoron_ai {

static void append_string(
    std::vector<std::uint8_t>& out,
    const std::string& value
) {
    const auto size = static_cast<std::uint64_t>(value.size());

    for (int i = 0; i < 8; ++i) {
        out.push_back(static_cast<std::uint8_t>((size >> (i * 8)) & 0xff));
    }

    out.insert(out.end(), value.begin(), value.end());
}

std::vector<std::uint8_t> encode_runtime_input(
    const RuntimeInput& input
) {
    std::vector<std::uint8_t> out;

    append_string(out, input.goal.name);

    for (const auto& candidate : input.goal_candidates) {
        append_string(out, candidate.name);
    }

    for (const auto& observation : input.observations) {
        append_string(out, observation);
    }

    for (const auto& rule : input.rules) {
        append_string(out, rule.name);
        append_string(out, rule.left_payload);
        append_string(out, rule.right_payload);
        append_string(out, rule.conclusion_payload);
    }

    return out;
}

MemoryDigest commit_runtime_input(
    const RuntimeInput& input
) {
    const auto bytes = encode_runtime_input(input);
    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
