/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory_node.hpp"

#include <cstdint>
#include <vector>

namespace petoron_ai {

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

MemoryDigest commit_memory_node(
    const MemoryNode& node
) {
    std::vector<std::uint8_t> bytes;

    append_string(bytes, node.type);
    append_string(bytes, node.payload);

    for (const auto& link : node.links) {
        bytes.insert(
            bytes.end(),
            link.begin(),
            link.end()
        );
    }

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
