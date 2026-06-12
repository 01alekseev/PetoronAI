/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/goal_tree.hpp"
#include "petoron_ai/planning/planner.hpp"

#include <cstdlib>

int main() {
    const auto tree =
        petoron_ai::build_goal_tree(
            "avoid storm"
        );

    if (tree.goal != "avoid storm") {
        return EXIT_FAILURE;
    }

    if (tree.subgoals.size() != 3) {
        return EXIT_FAILURE;
    }

    const auto plan =
        petoron_ai::build_plan(tree);

    if (plan.size() != 3) {
        return EXIT_FAILURE;
    }

    if (plan[0].goal != "find shelter") {
        return EXIT_FAILURE;
    }

    if (plan[0].action != "search for shelter") {
        return EXIT_FAILURE;
    }

    if (plan[1].goal != "secure shelter") {
        return EXIT_FAILURE;
    }

    if (plan[1].action != "secure shelter entrance") {
        return EXIT_FAILURE;
    }

    if (plan[2].goal != "stay protected") {
        return EXIT_FAILURE;
    }

    if (plan[2].action != "stay inside shelter") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
