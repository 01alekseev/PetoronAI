/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_arbitration.hpp"

#include <cstdlib>

int main() {
    petoron_ai::Goal safe;
    safe.name = "stay safe";

    petoron_ai::Goal resources;
    resources.name = "collect resources";

    petoron_ai::Goal explore;
    explore.name = "explore world";

    const auto best =
        petoron_ai::select_active_goal({
            {safe, 100},
            {resources, 40},
            {explore, 20}
        });

    if (best.goal.name != "stay safe") {
        return EXIT_FAILURE;
    }

    const auto tie =
        petoron_ai::select_active_goal({
            {resources, 80},
            {safe, 80}
        });

    if (tie.goal.name != "collect resources") {
        return EXIT_FAILURE;
    }

    const auto empty =
        petoron_ai::select_active_goal({});

    if (!empty.goal.name.empty()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
