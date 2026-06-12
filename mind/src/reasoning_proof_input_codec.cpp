/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning_proof_input_codec.hpp"

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

std::vector<std::uint8_t> encode_reasoning_proof_input(
    const ReasoningProofInput& input
) {
    std::vector<std::uint8_t> out;

    append_digest(out, input.old_root);
    append_digest(out, input.new_root);
    append_digest(out, input.trace_id);

    return out;
}

MemoryDigest commit_reasoning_proof_input(
    const ReasoningProofInput& input
) {
    const auto bytes =
        encode_reasoning_proof_input(input);

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
