/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "butler_hands/audit_sink.hpp"
#include "butler_hands/environment.hpp"
#include "butler_hands/execution_policy.hpp"
#include "butler_hands/types.hpp"

#include "petoron_ai_butler.hpp"

#include <atomic>
#include <string>

namespace butler_hands {

class Runtime final {
public:
    Runtime(
        Environment& environment,
        ExecutionPolicy& policy,
        AuditSink& audit
    );

    RunResult run(
        const std::string& goal,
        const RuntimeConfig& config = {}
    );

    void cancel() noexcept;

private:
    Environment& environment_;
    ExecutionPolicy& policy_;
    AuditSink& audit_;
    petoron_ai_butler::Butler butler_;
    std::atomic_bool cancelled_{false};
};

}
