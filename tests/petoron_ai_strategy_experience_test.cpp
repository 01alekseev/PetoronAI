/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_experience.hpp"

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
        petoron_ai::make_strategy_experience(
            strategy,
            true,
            100
        );

    const auto failure =
        petoron_ai::make_strategy_experience(
            strategy,
            false,
            -50
        );

    const auto merged =
        petoron_ai::merge_strategy_experience(
            success,
            failure
        );

    if (success.success_count != 1) {
        return EXIT_FAILURE;
    }

    if (success.failure_count != 0) {
        return EXIT_FAILURE;
    }

    if (failure.success_count != 0) {
        return EXIT_FAILURE;
    }

    if (failure.failure_count != 1) {
        return EXIT_FAILURE;
    }

    if (merged.success_count != 1) {
        return EXIT_FAILURE;
    }

    if (merged.failure_count != 1) {
        return EXIT_FAILURE;
    }

    if (merged.reward_total != 50) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::strategy_success_rate(merged) != 50) {
        return EXIT_FAILURE;
    }

    if (success.id == merged.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
