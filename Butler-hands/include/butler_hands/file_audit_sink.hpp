/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "butler_hands/audit_sink.hpp"

#include <filesystem>

namespace butler_hands {

class FileAuditSink final : public AuditSink {
public:
    explicit FileAuditSink(std::filesystem::path path);
    void record(const CycleRecord& record) override;

private:
    std::filesystem::path path_;
};

}
