/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/outcome_evaluation.hpp"

#include <cstdlib>

int main() {
    const auto shelter =
        petoron_ai::evaluate_outcome(
            "safe shelter reached"
        );

    if (!shelter.goal_achieved) {
        return EXIT_FAILURE;
    }

    if (shelter.utility != 100) {
        return EXIT_FAILURE;
    }

    const auto unknown =
        petoron_ai::evaluate_outcome(
            "unknown"
        );

    if (unknown.goal_achieved) {
        return EXIT_FAILURE;
    }

    if (unknown.utility != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
