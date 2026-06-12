/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

struct ActionResult {
    std::string action;
    bool success = false;
    std::string outcome;
};

ActionResult execute_action(
    const std::string& action
);

}
