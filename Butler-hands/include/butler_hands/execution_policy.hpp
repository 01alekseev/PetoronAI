/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "butler_hands/types.hpp"

#include <string>

namespace butler_hands {

class ExecutionPolicy {
public:
    virtual ~ExecutionPolicy() = default;

    virtual bool allow(
        const ExecutionRequest& request,
        std::string& reason
    ) const = 0;
};

class AllowAllExecutionPolicy final : public ExecutionPolicy {
public:
    bool allow(
        const ExecutionRequest&,
        std::string& reason
    ) const override {
        reason.clear();
        return true;
    }
};

}
