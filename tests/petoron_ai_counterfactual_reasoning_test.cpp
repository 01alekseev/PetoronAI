/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning/counterfactual_reasoning.hpp"

#include <cstdlib>

int main() {
    const auto shelter =
        petoron_ai::compare_futures(
            "find shelter",
            10,
            "do nothing",
            90
        );

    if (shelter.preferred_action != "find shelter") {
        return EXIT_FAILURE;
    }

    const auto escape =
        petoron_ai::compare_futures(
            "stay near fire",
            80,
            "move away",
            20
        );

    if (escape.preferred_action != "move away") {
        return EXIT_FAILURE;
    }

    const auto tie =
        petoron_ai::compare_futures(
            "strategy_a",
            50,
            "strategy_b",
            50
        );

    if (tie.preferred_action != "strategy_a") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
