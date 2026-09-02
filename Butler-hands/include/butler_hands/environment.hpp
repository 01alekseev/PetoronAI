/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "butler_hands/execution_context.hpp"
#include "butler_hands/types.hpp"

#include <cstdint>
#include <string>

namespace butler_hands {

class Environment {
public:
    virtual ~Environment() = default;

    virtual EnvironmentSnapshot observe(
        const std::string& goal,
        std::uint64_t cycle
    ) = 0;

    virtual ExecutionResult execute(
        const ExecutionRequest& request,
        const ExecutionContext& context
    ) = 0;
};

}
