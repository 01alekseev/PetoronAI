/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

std::vector<std::string> apply_world_transition(
    const std::vector<std::string>& world_facts,
    const std::string& action
);

}
