/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_adaptation.hpp"

#include <cstdlib>

int main() {
    petoron_ai::GoalAdaptationState state;

    petoron_ai::apply_goal_feedback(
        state,
        "find shelter",
        100
    );

    petoron_ai::apply_goal_feedback(
        state,
        "find shelter",
        50
    );

    petoron_ai::apply_goal_feedback(
        state,
        "explore storm",
        -30
    );

    if (
        petoron_ai::get_goal_priority(
            state,
            "find shelter"
        ) != 150
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::get_goal_priority(
            state,
            "explore storm"
        ) != -30
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::get_goal_priority(
            state,
            "unknown"
        ) != 0
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
