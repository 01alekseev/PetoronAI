/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_conflict_resolver.hpp"

#include <cstdlib>

int main() {
    petoron_ai::Goal safe;
    safe.name = "stay safe";

    petoron_ai::Goal leave;
    leave.name = "leave shelter";

    const auto first =
        petoron_ai::resolve_goal_conflict(
            {safe, 100},
            {leave, 90}
        );

    if (first.winner != "stay safe") {
        return EXIT_FAILURE;
    }

    if (first.loser != "leave shelter") {
        return EXIT_FAILURE;
    }

    petoron_ai::Goal resources;
    resources.name = "collect resources";

    const auto second =
        petoron_ai::resolve_goal_conflict(
            {resources, 120},
            {safe, 100}
        );

    if (second.winner != "collect resources") {
        return EXIT_FAILURE;
    }

    if (second.loser != "stay safe") {
        return EXIT_FAILURE;
    }

    const auto tie =
        petoron_ai::resolve_goal_conflict(
            {safe, 100},
            {resources, 100}
        );

    if (tie.winner != "stay safe") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
