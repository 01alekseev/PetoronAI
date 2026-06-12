/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/state/mind_state_file.hpp"

#include <fstream>
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
            static_cast<std::uint64_t>(bytes[offset + i]) << (i * 8);
    }

    offset += 8;
    return true;
}

bool write_mind_state_file(
    const std::string& path,
    const MindState& state
) {
    std::vector<std::uint8_t> bytes;

    bytes.push_back('P');
    bytes.push_back('M');
    bytes.push_back('S');
    bytes.push_back('F');
    bytes.push_back(1);

    append_digest(bytes, state.current_kb_id);
    append_digest(bytes, state.transition_chain_id);
    append_digest(bytes, state.last_cycle_id);
    append_u64(bytes, state.cycle_count);

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

bool read_mind_state_file(
    const std::string& path,
    MindState& state
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

    std::vector<std::uint8_t> bytes(
        static_cast<std::size_t>(size)
    );

    if (!bytes.empty()) {
        in.read(
            reinterpret_cast<char*>(bytes.data()),
            static_cast<std::streamsize>(bytes.size())
        );
    }

    const std::size_t expected_size =
        5 + MemoryDigest{}.size() * 3 + 8;

    if (bytes.size() != expected_size) {
        return false;
    }

    if (
        bytes[0] != 'P' ||
        bytes[1] != 'M' ||
        bytes[2] != 'S' ||
        bytes[3] != 'F' ||
        bytes[4] != 1
    ) {
        return false;
    }

    std::size_t offset = 5;

    if (!read_digest(bytes, offset, state.current_kb_id)) {
        return false;
    }

    if (!read_digest(bytes, offset, state.transition_chain_id)) {
        return false;
    }

    if (!read_digest(bytes, offset, state.last_cycle_id)) {
        return false;
    }

    if (!read_u64(bytes, offset, state.cycle_count)) {
        return false;
    }

    return offset == bytes.size();
}

}
