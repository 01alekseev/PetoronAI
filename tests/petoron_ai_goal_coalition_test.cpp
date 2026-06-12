/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_coalition.hpp"

#include <cstdlib>

int main() {
    petoron_ai::Goal safe;
    safe.name = "stay safe";

    petoron_ai::Goal resources;
    resources.name = "collect resources";

    petoron_ai::Goal explore;
    explore.name = "explore world";

    const auto coalition =
        petoron_ai::build_goal_coalition(
            {
                {safe, 100},
                {resources, 80},
                {explore, 20}
            },
            50
        );

    if (coalition.goals.size() != 2) {
        return EXIT_FAILURE;
    }

    if (coalition.total_priority != 180) {
        return EXIT_FAILURE;
    }

    if (coalition.goals[0].goal.name != "stay safe") {
        return EXIT_FAILURE;
    }

    if (coalition.goals[1].goal.name != "collect resources") {
        return EXIT_FAILURE;
    }

    const auto empty =
        petoron_ai::build_goal_coalition(
            {
                {explore, 20}
            },
            50
        );

    if (!empty.goals.empty()) {
        return EXIT_FAILURE;
    }

    if (empty.total_priority != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
