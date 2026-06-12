/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/action_execution.hpp"

namespace petoron_ai {

ActionResult execute_action(
    const std::string& action
) {
    ActionResult result;

    result.action = action;

    if (action == "find shelter") {
        result.success = true;
        result.outcome = "safe shelter reached";
    } else if (action == "leave area") {
        result.success = true;
        result.outcome = "area evacuated";
    } else if (action == "wait for storm to pass") {
        result.success = true;
        result.outcome = "storm survived";
    } else {
        result.success = false;
        result.outcome = "action unknown";
    }

    return result;
}

}
