/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/feedback_engine.hpp"

namespace petoron_ai {

static bool ends_with(
    const std::string& value,
    const std::string& suffix
) {
    if (value.size() < suffix.size()) {
        return false;
    }

    return value.compare(
        value.size() - suffix.size(),
        suffix.size(),
        suffix
    ) == 0;
}

static bool has_action(
    const std::vector<ActionResult>& results,
    const std::string& action
) {
    for (const auto& result : results) {
        if (result.action == action && result.success) {
            return true;
        }
    }

    return false;
}

std::vector<MemoryTransition> learn_from_actions(
    PetoronMind& mind,
    const std::vector<ActionResult>& results
) {
    std::vector<MemoryTransition> transitions;

    bool any_success = false;

    for (const auto& result : results) {
        if (!result.success) {
            continue;
        }

        any_success = true;

        const auto transition =
            mind.observe(result.outcome);

        transitions.push_back(transition);
    }

    if (any_success && mind.find_by_payload("plan succeeded") == nullptr) {
        transitions.push_back(
            mind.observe("plan succeeded")
        );
    }

    if (
        has_action(results, "move away") &&
        has_action(results, "stabilize body") &&
        has_action(results, "avoid injury") &&
        mind.find_by_payload("injury risk handled") == nullptr
    ) {
        transitions.push_back(
            mind.observe("injury risk handled")
        );
    }

    for (const auto& result : results) {
        if (!result.success || !result.action.starts_with("avoid ")) {
            continue;
        }

        const std::string active_goal =
            "active goal:" + result.action;

        if (mind.find_by_payload(active_goal) == nullptr) {
            transitions.push_back(
                mind.observe(active_goal)
            );
        }
    }

    for (const auto& node : mind.graph().nodes) {
        if (!node.payload.starts_with("hypothesis:")) {
            continue;
        }

        const std::string confidence =
            "confidence:" + node.payload + ":60";

        if (mind.find_by_payload(confidence) == nullptr) {
            transitions.push_back(
                mind.observe(confidence)
            );
        }
    }

    for (const auto& node : mind.graph().nodes) {
        const std::string suffix = " is dangerous";

        if (!ends_with(node.payload, suffix)) {
            continue;
        }

        const std::string confidence =
            "confidence:" + node.payload + ":90";

        if (mind.find_by_payload(confidence) == nullptr) {
            transitions.push_back(
                mind.observe(confidence)
            );
        }
    }

    if (
        mind.find_by_payload("knowledge is unstable") != nullptr &&
        mind.find_by_payload("confidence:knowledge is unstable:95") == nullptr
    ) {
        transitions.push_back(
            mind.observe("confidence:knowledge is unstable:95")
        );
    }

    for (const auto& node : mind.graph().nodes) {
        const std::string suffix = " is dangerous";

        if (!ends_with(node.payload, suffix)) {
            continue;
        }

        const auto target =
            node.payload.substr(0, node.payload.size() - suffix.size());

        const std::string hypothesis =
            "hypothesis:" + target + " exists";

        if (mind.find_by_payload(hypothesis) != nullptr) {
            const std::string explanation =
                "explain:" + node.payload + ":" + hypothesis;

            if (mind.find_by_payload(explanation) == nullptr) {
                transitions.push_back(
                    mind.observe(explanation)
                );
            }
        }

        const std::string action =
            "avoid " + target;

        if (has_action(results, action)) {
            const std::string explanation =
                "explain:" + action + ":" + node.payload;

            if (mind.find_by_payload(explanation) == nullptr) {
                transitions.push_back(
                    mind.observe(explanation)
                );
            }
        }
    }

    if (
        has_action(results, "avoid injury") &&
        mind.find_by_payload("injury is dangerous") != nullptr &&
        mind.find_by_payload("explain:avoid injury:injury is dangerous") == nullptr
    ) {
        transitions.push_back(
            mind.observe("explain:avoid injury:injury is dangerous")
        );
    }

    for (const auto& result : results) {
        if (!result.success || result.action.empty()) {
            continue;
        }

        const std::string strategy =
            "strategy:" + result.action + " effective";

        if (mind.find_by_payload(strategy) == nullptr) {
            transitions.push_back(
                mind.observe(strategy)
            );
        }

        const std::string score =
            "strategy_score:" + result.action + ":1";

        if (mind.find_by_payload(score) == nullptr) {
            transitions.push_back(
                mind.observe(score)
            );
        }
    }

    return transitions;
}

}
