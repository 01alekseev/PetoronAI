/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/decision_selector.hpp"

#include <cstdlib>

int main() {
    const auto selected =
        petoron_ai::select_best_hypothesis(
            {
                {"wait for storm to pass", 40},
                {"leave area", 80},
                {"find shelter", 100}
            }
        );

    if (selected != "find shelter") {
        return EXIT_FAILURE;
    }

    const auto empty =
        petoron_ai::select_best_hypothesis({});
    
    if (!empty.empty()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
