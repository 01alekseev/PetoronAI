/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning_rule.hpp"

namespace petoron_ai {

ReasoningResult apply_reasoning_rule(
    const MemoryNode& left,
    const MemoryNode& right,
    const ReasoningRule& rule
) {
    ReasoningResult result;
    result.valid = false;

    if (left.payload != rule.left_payload) {
        return result;
    }

    if (right.payload != rule.right_payload) {
        return result;
    }

    result.valid = true;
    result.conclusion.type = "conclusion";
    result.conclusion.payload = rule.conclusion_payload;
    result.conclusion.links.push_back(commit_memory_node(left));
    result.conclusion.links.push_back(commit_memory_node(right));

    return result;
}

}
