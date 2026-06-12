/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_state_transition.hpp"

namespace petoron_ai {

std::vector<std::string> apply_world_transition(
    const std::vector<std::string>& world_facts,
    const std::string& action
) {
    auto result = world_facts;

    if (action == "find shelter") {
        result.push_back("shelter occupied");
        result.push_back("risk reduced");
    }

    if (action == "collect resources") {
        result.push_back("resources collected");
    }

    return result;
}

}
