/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_feedback_delta.hpp"

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

    out.insert(out.end(), value.begin(), value.end());
}

std::vector<MemoryNode> knowledge_feedback_delta(
    const KnowledgeStore& old_store,
    const KnowledgeStore& new_store
) {
    std::vector<MemoryNode> out;

    for (const auto& fact : new_store.facts()) {
        if (old_store.has_fact(fact)) {
            continue;
        }

        MemoryNode node;
        node.type = "fact";
        node.payload = fact;
        out.push_back(node);
    }

    return out;
}

MemoryDigest commit_knowledge_feedback_delta(
    const KnowledgeStore& old_store,
    const KnowledgeStore& new_store
) {
    const auto delta =
        knowledge_feedback_delta(old_store, new_store);

    std::vector<std::uint8_t> bytes;

    for (const auto& node : delta) {
        append_string(bytes, node.type);
        append_string(bytes, node.payload);
    }

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

}
