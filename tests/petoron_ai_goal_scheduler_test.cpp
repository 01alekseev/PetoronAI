/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_scheduler.hpp"

#include <cstdlib>

int main() {
    const auto schedule =
        petoron_ai::schedule_goals(
            {
                "find shelter",
                "collect food",
                "find water",
                "explore storm",
                "build camp"
            }
        );

    if (schedule.current_goal != "find shelter") {
        return EXIT_FAILURE;
    }

    if (schedule.queued_goals.size() != 2) {
        return EXIT_FAILURE;
    }

    if (schedule.queued_goals[0] != "collect food") {
        return EXIT_FAILURE;
    }

    if (schedule.queued_goals[1] != "find water") {
        return EXIT_FAILURE;
    }

    if (schedule.deferred_goals.size() != 2) {
        return EXIT_FAILURE;
    }

    if (schedule.deferred_goals[0] != "explore storm") {
        return EXIT_FAILURE;
    }

    if (schedule.deferred_goals[1] != "build camp") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
