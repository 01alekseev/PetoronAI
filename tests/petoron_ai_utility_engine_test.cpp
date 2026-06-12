/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/utility_engine.hpp"

#include <cstdlib>

int main() {
    const petoron_ai::UtilityAssessment a{
        80,
        40,
        10,
        5,
        20
    };

    if (
        petoron_ai::compute_utility(a)
        != 125
    ) {
        return EXIT_FAILURE;
    }

    const petoron_ai::UtilityAssessment b{
        90,
        5,
        0,
        20,
        0
    };

    if (
        petoron_ai::compute_utility(b)
        != 75
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::compute_utility(a)
        <=
        petoron_ai::compute_utility(b)
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
