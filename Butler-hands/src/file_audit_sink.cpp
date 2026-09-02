/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/file_audit_sink.hpp"

#include <fstream>
#include <stdexcept>
#include <string_view>

namespace butler_hands {
namespace {

std::string escape(std::string_view value) {
    std::string out;
    out.reserve(value.size());

    for (const char ch : value) {
        switch (ch) {
            case '\\': out += "\\\\"; break;
            case '"': out += "\\\""; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default: out += ch; break;
        }
    }
    return out;
}

}

FileAuditSink::FileAuditSink(std::filesystem::path path)
    : path_(std::move(path)) {
    if (path_.empty()) {
        throw std::invalid_argument("audit path is empty");
    }
}

void FileAuditSink::record(const CycleRecord& record) {
    if (path_.has_parent_path()) {
        std::error_code ec;
        std::filesystem::create_directories(path_.parent_path(), ec);
        if (ec) {
            throw std::runtime_error("failed to create audit directory: " + ec.message());
        }
    }

    std::ofstream out(path_, std::ios::app);
    if (!out) {
        throw std::runtime_error("failed to open audit file");
    }

    out
        << "{\"session_id\":\"" << escape(record.session_id)
        << "\",\"cycle\":" << record.cycle
        << ",\"goal\":\"" << escape(record.goal)
        << "\",\"selected_capability\":\"" << escape(record.selected_capability)
        << "\",\"butler_explanation\":\"" << escape(record.butler_explanation)
        << "\",\"execution_success\":" << (record.execution_success ? "true" : "false")
        << ",\"execution_outcome\":\"" << escape(record.execution_outcome)
        << "\",\"execution_reward\":" << record.execution_reward
        << "}\n";

    if (!out) {
        throw std::runtime_error("failed to write audit record");
    }
}

}
