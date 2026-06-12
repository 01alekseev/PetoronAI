/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_simulation.hpp"

#include <algorithm>
#include <cstdlib>

int main() {
    const auto shelter =
        petoron_ai::simulate_world(
            {
                "storm exists"
            },
            "find shelter"
        );

    if (shelter.risk != 10) {
        return EXIT_FAILURE;
    }

    if (
        std::find(
            shelter.facts.begin(),
            shelter.facts.end(),
            "risk reduced"
        ) == shelter.facts.end()
    ) {
        return EXIT_FAILURE;
    }

    const auto idle =
        petoron_ai::simulate_world(
            {
                "storm exists"
            },
            "do nothing"
        );

    if (idle.risk != 90) {
        return EXIT_FAILURE;
    }

    const auto resources =
        petoron_ai::simulate_world(
            {},
            "collect resources"
        );

    if (resources.risk != 40) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
