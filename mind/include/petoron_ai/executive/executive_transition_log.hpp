/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_controller.hpp"

#include <vector>

namespace petoron_ai {

class ExecutiveTransitionLog {
public:
    void record(ExecutiveState state);

    [[nodiscard]]
    const std::vector<ExecutiveState>& history() const;

    [[nodiscard]]
    std::size_t size() const;

private:
    std::vector<ExecutiveState> history_;
};

}
