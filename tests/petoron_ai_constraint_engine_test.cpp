/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/constraint_engine.hpp"

#include <cstdlib>

int main() {
    const auto blocked =
        petoron_ai::evaluate_constraints(
            {
                "storm exists",
                "dark clouds visible"
            },
            {
                {
                    "storm exists",
                    "go outside"
                }
            },
            "go outside"
        );

    if (blocked.allowed) {
        return EXIT_FAILURE;
    }

    if (blocked.reason != "storm exists") {
        return EXIT_FAILURE;
    }

    const auto allowed =
        petoron_ai::evaluate_constraints(
            {
                "storm exists"
            },
            {
                {
                    "storm exists",
                    "go outside"
                }
            },
            "find shelter"
        );

    if (!allowed.allowed) {
        return EXIT_FAILURE;
    }

    const auto no_constraints =
        petoron_ai::evaluate_constraints(
            {},
            {},
            "collect resources"
        );

    if (!no_constraints.allowed) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
