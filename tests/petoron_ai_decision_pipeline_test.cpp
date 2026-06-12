/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/decision_pipeline.hpp"

#include <cstdlib>

int main() {
    const auto policy =
        petoron_ai::build_policy({
            {"find shelter", 105},
            {"keep distance", 70},
            {"walk into storm", -110}
        });

    const auto result =
        petoron_ai::run_decision_pipeline(
            policy,
            {
                {"find shelter", 105},
                {"keep distance", 70},
                {"walk into storm", -110}
            },
            {
                "storm exists"
            },
            {
                {
                    "storm exists",
                    "walk into storm"
                }
            }
        );

    if (!result.allowed) {
        return EXIT_FAILURE;
    }

    if (result.selected_strategy != "find shelter") {
        return EXIT_FAILURE;
    }

    const auto blocked =
        petoron_ai::run_decision_pipeline(
            policy,
            {
                {"walk into storm", -110}
            },
            {
                "storm exists"
            },
            {
                {
                    "storm exists",
                    "walk into storm"
                }
            }
        );

    if (blocked.allowed) {
        return EXIT_FAILURE;
    }

    if (!blocked.selected_strategy.empty()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
