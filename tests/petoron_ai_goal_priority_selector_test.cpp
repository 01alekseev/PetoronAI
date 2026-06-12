/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_priority_selector.hpp"

#include <cstdlib>

int main() {
    petoron_ai::GoalAdaptationState state;

    state.goal_priority["collect food"] = 80;
    state.goal_priority["find shelter"] = 150;
    state.goal_priority["explore storm"] = -30;

    const auto selected =
        petoron_ai::select_primary_goal(
            state
        );

    if (selected != "find shelter") {
        return EXIT_FAILURE;
    }

    petoron_ai::GoalAdaptationState empty;

    if (
        !petoron_ai::select_primary_goal(
            empty
        ).empty()
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
