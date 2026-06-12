/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/state/mind_state.hpp"

#include "proof/commitment/petoron_zk_commitment.hpp"

#include <vector>

namespace petoron_ai {

static void append_digest(
    std::vector<std::uint8_t>& out,
    const MemoryDigest& digest
) {
    out.insert(out.end(), digest.begin(), digest.end());
}

static void append_u64(
    std::vector<std::uint8_t>& out,
    std::uint64_t value
) {
    for (int i = 0; i < 8; ++i) {
        out.push_back(
            static_cast<std::uint8_t>(
                (value >> (i * 8)) & 0xff
            )
        );
    }
}

MemoryDigest commit_mind_state(
    const MindState& state
) {
    std::vector<std::uint8_t> bytes;

    append_digest(bytes, state.current_kb_id);
    append_digest(bytes, state.transition_chain_id);
    append_digest(bytes, state.last_cycle_id);
    append_u64(bytes, state.cycle_count);

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
