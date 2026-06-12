/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning/hypothesis_evaluation.hpp"

#include <cstdlib>

int main() {
    const auto evaluated =
        petoron_ai::evaluate_hypotheses(
            {
                "find shelter",
                "leave area",
                "wait for storm to pass",
                "unknown"
            }
        );

    if (evaluated.size() != 4) {
        return EXIT_FAILURE;
    }

    if (evaluated[0].score != 100) {
        return EXIT_FAILURE;
    }

    if (evaluated[1].score != 80) {
        return EXIT_FAILURE;
    }

    if (evaluated[2].score != 40) {
        return EXIT_FAILURE;
    }

    if (evaluated[3].score != 10) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
