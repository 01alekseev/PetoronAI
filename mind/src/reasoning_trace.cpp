/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning_trace.hpp"

namespace petoron_ai {

ReasoningTrace build_reasoning_trace(
    const ReasoningTransition& transition
) {
    ReasoningTrace trace;
    trace.old_root = transition.old_root;
    trace.new_root = transition.new_root;
    trace.left_commitment = commit_memory_node(transition.left);
    trace.right_commitment = commit_memory_node(transition.right);
    trace.conclusion_commitment =
        commit_memory_node(transition.conclusion);
    trace.rule_name = transition.rule.name;
    return trace;
}

bool verify_reasoning_trace(
    const ReasoningTransition& transition,
    const ReasoningTrace& trace
) {
    if (trace.old_root != transition.old_root) {
        return false;
    }

    if (trace.new_root != transition.new_root) {
        return false;
    }

    if (trace.left_commitment != commit_memory_node(transition.left)) {
        return false;
    }

    if (trace.right_commitment != commit_memory_node(transition.right)) {
        return false;
    }

    if (trace.conclusion_commitment !=
        commit_memory_node(transition.conclusion)) {
        return false;
    }

    return trace.rule_name == transition.rule.name;
}

}
