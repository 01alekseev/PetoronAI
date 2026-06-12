/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/experience/self_improvement.hpp"

#include <cstdlib>

int main() {
    petoron_ai::SelfImprovementState state;

    petoron_ai::apply_outcome_feedback(
        state,
        "find shelter",
        100
    );

    petoron_ai::apply_outcome_feedback(
        state,
        "find shelter",
        50
    );

    petoron_ai::apply_outcome_feedback(
        state,
        "wait for storm to pass",
        -20
    );

    if (
        petoron_ai::get_action_confidence(
            state,
            "find shelter"
        ) != 150
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::get_action_confidence(
            state,
            "wait for storm to pass"
        ) != -20
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::get_action_confidence(
            state,
            "unknown"
        ) != 0
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
