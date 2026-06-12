/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_feedback.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    const auto positive =
        evaluate_executive_feedback(
            10,
            2
        );

    if (!positive.positive) {
        return EXIT_FAILURE;
    }

    if (positive.negative) {
        return EXIT_FAILURE;
    }

    const auto negative =
        evaluate_executive_feedback(
            2,
            10
        );

    if (!negative.negative) {
        return EXIT_FAILURE;
    }

    if (negative.positive) {
        return EXIT_FAILURE;
    }

    const auto neutral =
        evaluate_executive_feedback(
            5,
            5
        );

    if (
        neutral.positive ||
        neutral.negative
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
