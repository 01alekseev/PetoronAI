/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"

#include <string>

namespace petoron_ai {

struct ReasoningRule {
    std::string name;
    std::string left_payload;
    std::string right_payload;
    std::string conclusion_payload;
};

struct ReasoningResult {
    bool valid;
    MemoryNode conclusion;
};

ReasoningResult apply_reasoning_rule(
    const MemoryNode& left,
    const MemoryNode& right,
    const ReasoningRule& rule
);

}
