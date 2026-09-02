/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "butler_hands/types.hpp"

namespace butler_hands {

class AuditSink {
public:
    virtual ~AuditSink() = default;
    virtual void record(const CycleRecord& record) = 0;
};

class NullAuditSink final : public AuditSink {
public:
    void record(const CycleRecord&) override {}
};

}
