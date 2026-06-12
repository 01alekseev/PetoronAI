/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_stack.hpp"

#include <cstdlib>

int main() {
    petoron_ai::GoalAdaptationState state;

    state.goal_priority["collect food"] = 80;
    state.goal_priority["find shelter"] = 150;
    state.goal_priority["explore storm"] = -30;

    const auto stack =
        petoron_ai::build_goal_stack(
            state
        );

    if (stack.size() != 3) {
        return EXIT_FAILURE;
    }

    if (stack[0] != "find shelter") {
        return EXIT_FAILURE;
    }

    if (stack[1] != "collect food") {
        return EXIT_FAILURE;
    }

    if (stack[2] != "explore storm") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
