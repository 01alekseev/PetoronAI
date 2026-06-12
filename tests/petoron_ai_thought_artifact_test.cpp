/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_artifact.hpp"

#include <cstdlib>

int main() {
    const auto a =
        petoron_ai::make_thought_artifact(
            "storm requires shelter",
            "storm is dangerous",
            "avoid storm",
            90
        );

    const auto b =
        petoron_ai::make_thought_artifact(
            "storm requires shelter",
            "storm is dangerous",
            "avoid storm",
            90
        );

    const auto c =
        petoron_ai::make_thought_artifact(
            "fire requires distance",
            "fire is dangerous",
            "avoid fire",
            90
        );

    if (a.thought != "storm requires shelter") {
        return EXIT_FAILURE;
    }

    if (a.reason != "storm is dangerous") {
        return EXIT_FAILURE;
    }

    if (a.source_goal != "avoid storm") {
        return EXIT_FAILURE;
    }

    if (a.confidence != 90) {
        return EXIT_FAILURE;
    }

    if (a.id != b.id) {
        return EXIT_FAILURE;
    }

    if (a.id == c.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
