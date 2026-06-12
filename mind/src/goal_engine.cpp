/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal_engine.hpp"

namespace petoron_ai {

static bool starts_with(
    const std::string& value,
    const std::string& prefix
) {
    return value.rfind(prefix, 0) == 0;
}

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

static std::string remove_suffix(
    const std::string& value,
    const std::string& suffix
) {
    return value.substr(0, value.size() - suffix.size());
}

static int priority_for_target(
    const std::string& target
) {
    if (target == "injury") {
        return 100;
    }

    if (target == "fire") {
        return 90;
    }

    if (target == "thirst") {
        return 80;
    }

    if (target == "danger") {
        return 70;
    }

    return 10;
}

Plan build_plan(
    const PetoronMind& mind,
    const Goal& goal
) {
    Plan plan;
    plan.goal = goal;

    if (goal.name == "auto") {
        const std::string suffix = " is dangerous";

        std::string best_target;
        std::string best_reason;
        int best_priority = -1;

        for (const auto& node : mind.graph().nodes) {
            if (!ends_with(node.payload, suffix)) {
                continue;
            }

            const auto target = remove_suffix(node.payload, suffix);
            const auto priority = priority_for_target(target);

            if (priority <= best_priority) {
                continue;
            }

            best_priority = priority;
            best_target = target;
            best_reason = node.payload;
        }

        if (!best_target.empty()) {
            if (best_target == "injury") {
                PlanStep step1;
                step1.action = "move away";
                step1.reason = best_reason;
                plan.steps.push_back(step1);

                PlanStep step2;
                step2.action = "stabilize body";
                step2.reason = best_reason;
                plan.steps.push_back(step2);

                PlanStep step3;
                step3.action = "avoid injury";
                step3.reason = best_reason;
                plan.steps.push_back(step3);

                return plan;
            }

            PlanStep step;
            step.action = "avoid " + best_target;
            step.reason = best_reason;
            plan.steps.push_back(step);
        }

        return plan;
    }

    if (goal.name == "avoid danger") {
        const std::string suffix = " is dangerous";

        for (const auto& node : mind.graph().nodes) {
            if (!ends_with(node.payload, suffix)) {
                continue;
            }

            const auto target = remove_suffix(node.payload, suffix);

            PlanStep step;
            step.action = "avoid " + target;
            step.reason = node.payload;
            plan.steps.push_back(step);
            return plan;
        }

        return plan;
    }

    if (starts_with(goal.name, "avoid ")) {
        const auto target = goal.name.substr(6);

        const std::string risk_a = target + " is dangerous";
        const std::string risk_b = "body is " + target;
        const std::string action = "avoid " + target;

        if (mind.find_by_payload(risk_a) != nullptr) {
            PlanStep step;
            step.action = action;
            step.reason = risk_a;
            plan.steps.push_back(step);
            return plan;
        }

        if (mind.find_by_payload(risk_b) != nullptr) {
            PlanStep step;
            step.action = action;
            step.reason = risk_b;
            plan.steps.push_back(step);
            return plan;
        }
    }

    return plan;
}

}
