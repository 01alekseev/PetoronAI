/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_simulation.hpp"
#include "petoron_ai/world/world_state_transition.hpp"

namespace petoron_ai {

SimulatedFuture simulate_world(
    const std::vector<std::string>& world_facts,
    const std::string& action
) {
    SimulatedFuture future;

    future.facts =
        apply_world_transition(
            world_facts,
            action
        );

    if (action == "find shelter") {
        future.risk = 10;
    } else if (action == "collect resources") {
        future.risk = 40;
    } else if (action == "do nothing") {
        future.risk = 90;
    } else {
        future.risk = 50;
    }

    return future;
}

}
