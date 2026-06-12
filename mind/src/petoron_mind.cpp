/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/petoron_mind.hpp"

namespace petoron_ai {

const MemoryGraph& PetoronMind::graph() const {
    return graph_;
}

MemoryDigest PetoronMind::root() const {
    return commit_memory_graph(graph_);
}

const MemoryNode* PetoronMind::find_by_payload(
    const std::string& payload
) const {
    for (const auto& node : graph_.nodes) {
        if (node.payload == payload) {
            return &node;
        }
    }

    return nullptr;
}

MemoryTransition PetoronMind::observe(
    const std::string& observation
) {
    const auto transition =
        apply_observation(graph_, observation);

    graph_.nodes.push_back(transition.new_node);

    return transition;
}

ReasoningTransition PetoronMind::reason(
    const MemoryNode& left,
    const MemoryNode& right,
    const ReasoningRule& rule
) {
    const auto transition =
        apply_reasoning_transition(
            graph_,
            left,
            right,
            rule
        );

    if (verify_reasoning_transition(graph_, transition)) {
        graph_.nodes.push_back(transition.conclusion);
    }

    return transition;
}

ReasoningTransition PetoronMind::reason_by_payload(
    const std::string& left_payload,
    const std::string& right_payload,
    const ReasoningRule& rule
) {
    const auto* left = find_by_payload(left_payload);
    const auto* right = find_by_payload(right_payload);

    if (left == nullptr || right == nullptr) {
        return ReasoningTransition{};
    }

    return reason(*left, *right, rule);
}

std::vector<ReasoningTransition> PetoronMind::autoreason(
    const std::vector<ReasoningRule>& rules
) {
    std::vector<ReasoningTransition> transitions;

    bool changed = true;

    while (changed) {
        changed = false;

        for (const auto& rule : rules) {
            if (find_by_payload(rule.conclusion_payload) != nullptr) {
                continue;
            }

            const auto* left = find_by_payload(rule.left_payload);
            const auto* right = find_by_payload(rule.right_payload);

            if (left == nullptr || right == nullptr) {
                continue;
            }

            const auto transition =
                reason(*left, *right, rule);

            if (find_by_payload(rule.conclusion_payload) != nullptr) {
                transitions.push_back(transition);
                changed = true;
            }
        }
    }

    return transitions;
}

}
