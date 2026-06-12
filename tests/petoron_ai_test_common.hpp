/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

namespace petoron_ai_test {

namespace fs = std::filesystem;

inline std::string shell_quote(const std::string& value) {
    std::string out = "'";
    for (const char c : value) {
        if (c == '\'') {
            out += "'\\''";
        } else {
            out += c;
        }
    }
    out += "'";
    return out;
}

inline std::string command_line(const std::vector<std::string>& args) {
    std::string out;
    for (const auto& arg : args) {
        if (!out.empty()) {
            out += " ";
        }
        out += shell_quote(arg);
    }
    return out;
}

inline int status(const std::vector<std::string>& args) {
    return std::system((command_line(args) + " > /dev/null 2>&1").c_str());
}

inline void run(const std::vector<std::string>& args) {
    const int rc = status(args);
    if (rc != 0) {
        std::cerr << "command failed: " << command_line(args) << "\n";
        std::exit(10);
    }
}

inline std::string output(const std::vector<std::string>& args) {
    const auto command = command_line(args) + " 2>&1";
    std::array<char, 512> buffer{};
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe == nullptr) {
        std::exit(11);
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
        result += buffer.data();
    }
    const int rc = pclose(pipe);
    if (rc != 0) {
        std::cerr << result;
        std::exit(12);
    }
    return result;
}

inline void write_text(const fs::path& path, const std::string& text) {
    fs::create_directories(path.parent_path());
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        std::exit(13);
    }
    out << text;
}

inline std::string read_text(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::exit(14);
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

inline std::vector<unsigned char> read_binary(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::exit(15);
    }
    return std::vector<unsigned char>(
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>()
    );
}

inline void write_binary(const fs::path& path, const std::vector<unsigned char>& data) {
    fs::create_directories(path.parent_path());
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        std::exit(16);
    }
    out.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
}

inline bool contains(const std::string& text, const std::string& needle) {
    return text.find(needle) != std::string::npos;
}

inline void require_contains(const std::string& text, const std::string& needle) {
    if (!contains(text, needle)) {
        std::cerr << "missing: " << needle << "\n" << text << "\n";
        std::exit(20);
    }
}

inline void require_absent(const std::string& text, const std::string& needle) {
    if (contains(text, needle)) {
        std::cerr << "forbidden: " << needle << "\n" << text << "\n";
        std::exit(21);
    }
}

inline void require_all(const std::string& text, const std::vector<std::string>& items) {
    for (const auto& item : items) {
        require_contains(text, item);
    }
}

inline void require_absent_all(const std::string& text, const std::vector<std::string>& items) {
    for (const auto& item : items) {
        require_absent(text, item);
    }
}

inline std::string extract_value(const std::string& label, const std::string& text) {
    const std::string prefix = label + ": ";
    std::size_t start = 0;
    while (start <= text.size()) {
        const auto end = text.find('\n', start);
        const auto line = text.substr(start, end == std::string::npos ? std::string::npos : end - start);
        if (line.rfind(prefix, 0) == 0) {
            return line.substr(prefix.size());
        }
        if (end == std::string::npos) {
            break;
        }
        start = end + 1;
    }
    return {};
}

inline void replace_first(std::string& text, const std::string& from, const std::string& to) {
    const auto pos = text.find(from);
    if (pos == std::string::npos) {
        std::exit(22);
    }
    text.replace(pos, from.size(), to);
}

inline std::vector<unsigned char> slice_bytes(
    const std::vector<unsigned char>& data,
    std::size_t offset,
    std::size_t size
) {
    if (offset + size > data.size()) {
        std::exit(23);
    }
    return std::vector<unsigned char>(data.begin() + static_cast<std::ptrdiff_t>(offset), data.begin() + static_cast<std::ptrdiff_t>(offset + size));
}

inline void overwrite_bytes(
    std::vector<unsigned char>& data,
    std::size_t offset,
    const std::vector<unsigned char>& value
) {
    if (offset + value.size() > data.size()) {
        std::exit(24);
    }
    std::copy(value.begin(), value.end(), data.begin() + static_cast<std::ptrdiff_t>(offset));
}

inline void append_u64_le(std::vector<unsigned char>& out, std::uint64_t value) {
    for (int i = 0; i < 8; ++i) {
        out.push_back(static_cast<unsigned char>((value >> (8 * i)) & 0xff));
    }
}


inline std::string exe(const fs::path& build, const std::string& name) {
    return (build / name).string();
}

}
