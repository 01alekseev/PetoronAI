/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/meta/meta_reasoning_artifact.hpp"

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

    const auto meta =
        petoron_ai::make_meta_reasoning_artifact(
            strategy
        );

    const auto meta2 =
        petoron_ai::make_meta_reasoning_artifact(
            strategy
        );

    if (meta.goal != "avoid storm") {
        return EXIT_FAILURE;
    }

    if (meta.selected_action != "find shelter") {
        return EXIT_FAILURE;
    }

    if (meta.strategy_score != 90) {
        return EXIT_FAILURE;
    }

    if (meta.confidence != 90) {
        return EXIT_FAILURE;
    }

    if (meta.explanation != "selected strategy has verified thought path") {
        return EXIT_FAILURE;
    }

    if (meta.id != meta2.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
