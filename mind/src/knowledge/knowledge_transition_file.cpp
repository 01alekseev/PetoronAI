/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_transition_file.hpp"
#include "petoron_ai/knowledge/knowledge_feedback_delta.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/runtime_input_codec.hpp"

#include <fstream>
#include <vector>

namespace petoron_ai {

static void append_digest(
    std::vector<std::uint8_t>& out,
    const MemoryDigest& digest
) {
    out.insert(out.end(), digest.begin(), digest.end());
}

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

static bool read_bytes(
    const std::string& path,
    std::vector<std::uint8_t>& bytes
) {
    std::ifstream in(path, std::ios::binary);

    if (!in) {
        return false;
    }

    in.seekg(0, std::ios::end);
    const auto size = in.tellg();
    in.seekg(0, std::ios::beg);

    if (size < 0) {
        return false;
    }

    bytes.resize(static_cast<std::size_t>(size));

    if (!bytes.empty()) {
        in.read(
            reinterpret_cast<char*>(bytes.data()),
            static_cast<std::streamsize>(bytes.size())
        );
    }

    return static_cast<bool>(in);
}

static bool write_bytes(
    const std::string& path,
    const std::vector<std::uint8_t>& bytes
) {
    std::ofstream out(path, std::ios::binary);

    if (!out) {
        return false;
    }

    out.write(
        reinterpret_cast<const char*>(bytes.data()),
        static_cast<std::streamsize>(bytes.size())
    );

    return static_cast<bool>(out);
}

bool write_knowledge_transition_file(
    const std::string& path,
    const KnowledgeTransitionFile& file
) {
    std::vector<std::uint8_t> bytes;

    bytes.push_back('P');
    bytes.push_back('K');
    bytes.push_back('B');
    bytes.push_back('T');
    bytes.push_back(1);

    append_digest(bytes, file.old_kb_id);
    append_digest(bytes, file.input_id);
    append_digest(bytes, file.cycle_id);
    append_digest(bytes, file.feedback_commitment);
    append_digest(bytes, file.new_kb_id);

    return write_bytes(path, bytes);
}

bool read_knowledge_transition_file(
    const std::string& path,
    KnowledgeTransitionFile& file
) {
    std::vector<std::uint8_t> bytes;

    if (!read_bytes(path, bytes)) {
        return false;
    }

    const std::size_t expected_size =
        5 + MemoryDigest{}.size() * 5;

    if (bytes.size() != expected_size) {
        return false;
    }

    if (
        bytes[0] != 'P' ||
        bytes[1] != 'K' ||
        bytes[2] != 'B' ||
        bytes[3] != 'T' ||
        bytes[4] != 1
    ) {
        return false;
    }

    std::size_t offset = 5;

    if (!read_digest(bytes, offset, file.old_kb_id)) {
        return false;
    }

    if (!read_digest(bytes, offset, file.input_id)) {
        return false;
    }

    if (!read_digest(bytes, offset, file.cycle_id)) {
        return false;
    }

    if (!read_digest(bytes, offset, file.feedback_commitment)) {
        return false;
    }

    if (!read_digest(bytes, offset, file.new_kb_id)) {
        return false;
    }

    return offset == bytes.size();
}

MemoryDigest commit_knowledge_transition_file(
    const KnowledgeTransitionFile& file
) {
    std::vector<std::uint8_t> bytes;

    append_digest(bytes, file.old_kb_id);
    append_digest(bytes, file.input_id);
    append_digest(bytes, file.cycle_id);
    append_digest(bytes, file.feedback_commitment);
    append_digest(bytes, file.new_kb_id);

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

MemoryDigest commit_knowledge_transition_chain(
    const std::vector<KnowledgeTransitionFile>& files
) {
    std::vector<std::uint8_t> bytes;

    for (const auto& file : files) {
        const auto transition_id =
            commit_knowledge_transition_file(file);

        append_digest(bytes, transition_id);
    }

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}
bool verify_knowledge_transition_file(
    const std::string& old_kb_path,
    const std::string& input_path,
    const std::string& cycle_path,
    const std::string& new_kb_path,
    const std::string& transition_path
) {
    KnowledgeStore old_store;

    if (!read_knowledge_file(old_kb_path, old_store)) {
        return false;
    }

    RuntimeInput input;

    if (!read_runtime_input(input_path, input)) {
        return false;
    }

    CycleFile cycle;

    if (!read_cycle_file(cycle_path, cycle)) {
        return false;
    }

    if (!verify_cycle_file(cycle)) {
        return false;
    }

    KnowledgeStore new_store;

    if (!read_knowledge_file(new_kb_path, new_store)) {
        return false;
    }

    KnowledgeTransitionFile transition;

    if (!read_knowledge_transition_file(transition_path, transition)) {
        return false;
    }

    const auto old_kb_id = old_store.root();
    const auto input_id = commit_runtime_input(input);
    const auto feedback_commitment =
        commit_knowledge_feedback_delta(
            old_store,
            new_store
        );
    const auto new_kb_id = new_store.root();

    if (transition.old_kb_id != old_kb_id) {
        return false;
    }

    if (transition.input_id != input_id) {
        return false;
    }

    if (transition.cycle_id != cycle.cycle_id) {
        return false;
    }

    if (transition.feedback_commitment != feedback_commitment) {
        return false;
    }

    if (transition.new_kb_id != new_kb_id) {
        return false;
    }

    if (cycle.trace.kb_id != old_kb_id) {
        return false;
    }

    if (cycle.trace.input_id != input_id) {
        return false;
    }

    if (old_kb_id == new_kb_id) {

        return false;
    }

    return true;
}

}
