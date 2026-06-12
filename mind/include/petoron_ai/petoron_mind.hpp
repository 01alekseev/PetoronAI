/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_transition.hpp"
#include "petoron_ai/reasoning_transition.hpp"

#include <vector>

namespace petoron_ai {

class PetoronMind {
public:
    const MemoryGraph& graph() const;
    MemoryDigest root() const;

    const MemoryNode* find_by_payload(
        const std::string& payload
    ) const;

    MemoryTransition observe(
        const std::string& observation
    );

    ReasoningTransition reason(
        const MemoryNode& left,
        const MemoryNode& right,
        const ReasoningRule& rule
    );

    ReasoningTransition reason_by_payload(
        const std::string& left_payload,
        const std::string& right_payload,
        const ReasoningRule& rule
    );

    std::vector<ReasoningTransition> autoreason(
        const std::vector<ReasoningRule>& rules
    );

private:
    MemoryGraph graph_;
};

}
