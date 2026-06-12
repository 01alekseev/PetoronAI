/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/cycle_file.hpp"

#include <fstream>
#include <vector>

namespace petoron_ai {

static void append_digest(
    std::vector<std::uint8_t>& out,
    const MemoryDigest& digest
) {
    out.insert(out.end(), digest.begin(), digest.end());
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

bool write_cycle_file(
    const std::string& path,
    const AgentCycleTrace& trace
) {
    const auto cycle_id =
        commit_agent_cycle_trace(trace);

    const auto trace_bytes =
        encode_agent_cycle_trace(trace);

    std::vector<std::uint8_t> file;
    file.push_back('P');
    file.push_back('A');
    file.push_back('I');
    file.push_back('C');
    file.push_back(1);

    append_digest(file, cycle_id);
    append_digest(file, trace.final_root);
    file.insert(file.end(), trace_bytes.begin(), trace_bytes.end());

    return write_bytes(path, file);
}

bool read_cycle_file(
    const std::string& path,
    CycleFile& file
) {
    std::vector<std::uint8_t> bytes;

    if (!read_bytes(path, bytes)) {
        return false;
    }

    const std::size_t header_size = 5;
    const std::size_t digest_size =
        MemoryDigest{}.size();

    const std::size_t min_size =
        header_size + digest_size + digest_size;

    if (bytes.size() < min_size) {
        return false;
    }

    if (
        bytes[0] != 'P' ||
        bytes[1] != 'A' ||
        bytes[2] != 'I' ||
        bytes[3] != 'C'
    ) {
        return false;
    }

    if (bytes[4] != 1) {
        return false;
    }

    std::size_t offset = header_size;

    for (std::size_t i = 0; i < digest_size; ++i) {
        file.cycle_id[i] = bytes[offset + i];
    }

    offset += digest_size;

    for (std::size_t i = 0; i < digest_size; ++i) {
        file.final_root[i] = bytes[offset + i];
    }

    offset += digest_size;

    std::vector<std::uint8_t> trace_bytes(
        bytes.begin() + static_cast<std::ptrdiff_t>(offset),
        bytes.end()
    );

    return decode_agent_cycle_trace(
        trace_bytes,
        file.trace
    );
}

bool verify_cycle_file(
    const CycleFile& file
) {
    if (file.cycle_id != commit_agent_cycle_trace(file.trace)) {
        return false;
    }

    return file.final_root == file.trace.final_root;
}

}
