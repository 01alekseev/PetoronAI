/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/action_engine.hpp"

namespace petoron_ai {

std::vector<ActionResult> execute_plan(
    const Plan& plan
) {
    std::vector<ActionResult> results;

    for (const auto& step : plan.steps) {
        ActionResult result;
        result.action = step.action;
        result.success = false;

        if (!step.action.empty()) {
            result.success = true;
            result.outcome = step.action + " completed";
        }

        results.push_back(result);
    }

    return results;
}

}
