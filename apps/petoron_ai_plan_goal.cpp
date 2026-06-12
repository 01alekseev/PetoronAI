/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/goal_tree.hpp"
#include "petoron_ai/planning/planner.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_plan_goal <goal>\n";
        return 1;
    }

    const auto tree =
        petoron_ai::build_goal_tree(argv[1]);

    const auto plan =
        petoron_ai::build_plan(tree);

    std::cout << "goal: " << tree.goal << "\n";

    int index = 1;

    for (const auto& step : plan) {
        std::cout << "step " << index << ": "
                  << step.action
                  << "\n";
        ++index;
    }

    return 0;
}
