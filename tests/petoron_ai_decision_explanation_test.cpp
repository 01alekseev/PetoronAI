/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/decision_explanation.hpp"

#include <cstdlib>

int main() {
    const auto explanation =
        petoron_ai::explain_decision(
            "find shelter",
            "storm exists",
            90
        );

    if (explanation.selected_action != "find shelter") {
        return EXIT_FAILURE;
    }

    if (explanation.reason != "storm exists") {
        return EXIT_FAILURE;
    }

    if (explanation.confidence != 90) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
