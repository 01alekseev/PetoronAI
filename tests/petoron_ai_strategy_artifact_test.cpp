/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_artifact.hpp"

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
            "shelter reduces storm exposure",
            "avoid storm",
            90
        );

    const auto c =
        petoron_ai::make_thought_artifact(
            "stay inside shelter",
            "inside shelter is safer",
            "avoid storm",
            100
        );

    const auto graph =
        petoron_ai::make_thought_graph(
            {a, b, c},
            {
                {a.id, b.id, 90},
                {b.id, c.id, 100}
            }
        );

    const auto path =
        petoron_ai::best_thought_path(
            graph,
            a.id
        );

    const auto shorter_graph =
        petoron_ai::make_thought_graph(
            {a, b, c},
            {
                {a.id, b.id, 90}
            }
        );

    const auto shorter_path =
        petoron_ai::best_thought_path(
            shorter_graph,
            a.id
        );

    const auto strategy =
        petoron_ai::make_strategy_artifact(
            "avoid storm",
            path,
            "find shelter"
        );

    const auto strategy2 =
        petoron_ai::make_strategy_artifact(
            "avoid storm",
            path,
            "find shelter"
        );

    const auto shorter_strategy =
        petoron_ai::make_strategy_artifact(
            "avoid storm",
            shorter_path,
            "find shelter"
        );

    if (!strategy.path.found) {
        return EXIT_FAILURE;
    }

    if (strategy.goal != "avoid storm") {
        return EXIT_FAILURE;
    }

    if (strategy.action != "find shelter") {
        return EXIT_FAILURE;
    }

    if (strategy.score != 190) {
        return EXIT_FAILURE;
    }

    if (strategy.id != strategy2.id) {
        return EXIT_FAILURE;
    }

    if (strategy.id == shorter_strategy.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
