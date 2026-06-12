/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_state_transition.hpp"

#include <algorithm>
#include <cstdlib>

int main() {
    const auto shelter =
        petoron_ai::apply_world_transition(
            {
                "storm exists"
            },
            "find shelter"
        );

    if (
        std::find(
            shelter.begin(),
            shelter.end(),
            "shelter occupied"
        ) == shelter.end()
    ) {
        return EXIT_FAILURE;
    }

    if (
        std::find(
            shelter.begin(),
            shelter.end(),
            "risk reduced"
        ) == shelter.end()
    ) {
        return EXIT_FAILURE;
    }

    const auto resources =
        petoron_ai::apply_world_transition(
            {},
            "collect resources"
        );

    if (
        std::find(
            resources.begin(),
            resources.end(),
            "resources collected"
        ) == resources.end()
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
