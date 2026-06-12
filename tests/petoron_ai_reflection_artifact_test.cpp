/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reflection/reflection_artifact.hpp"

#include <cstdlib>

int main() {
    const auto a =
        petoron_ai::make_thought_artifact(
            "storm exists",
            "dark clouds indicate storm",
            "avoid storm",
            80
        );

    const auto b =
        petoron_ai::make_thought_artifact(
            "find shelter",
            "shelter reduces exposure",
            "avoid storm",
            90
        );

    const auto graph =
        petoron_ai::make_thought_graph(
            {a, b},
            {
                {a.id, b.id, 90}
            }
        );

    const auto path =
        petoron_ai::best_thought_path(
            graph,
            a.id
        );

    const auto strategy =
        petoron_ai::make_strategy_artifact(
            "avoid storm",
            path,
            "find shelter"
        );

    const auto success =
        petoron_ai::make_reflection_artifact(
            strategy,
            true,
            100
        );

    const auto success2 =
        petoron_ai::make_reflection_artifact(
            strategy,
            true,
            100
        );

    const auto failure =
        petoron_ai::make_reflection_artifact(
            strategy,
            false,
            -50
        );

    if (success.goal != "avoid storm") {
        return EXIT_FAILURE;
    }

    if (success.action != "find shelter") {
        return EXIT_FAILURE;
    }

    if (!success.success) {
        return EXIT_FAILURE;
    }

    if (success.reward != 100) {
        return EXIT_FAILURE;
    }

    if (success.lesson != "strategy should be reinforced") {
        return EXIT_FAILURE;
    }

    if (failure.lesson != "strategy should be reconsidered") {
        return EXIT_FAILURE;
    }

    if (success.id != success2.id) {
        return EXIT_FAILURE;
    }

    if (success.id == failure.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
