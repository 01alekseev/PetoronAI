/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_scoring.hpp"

#include <cstdlib>

int main() {
    const auto model =
        petoron_ai::make_world_model({
            {"storm", "causes", "danger", 90},
            {"storm", "requires", "shelter", 95},
            {"fire", "requires", "distance", 70}
        });

    petoron_ai::Goal goal;
    goal.name = "stay safe";

    const auto impacts =
        petoron_ai::evaluate_goal_impact(
            model,
            goal
        );

    const auto scores =
        petoron_ai::score_strategies(
            impacts
        );

    bool shelter = false;
    bool distance = false;
    bool storm = false;

    for (const auto& score : scores) {
        if (
            score.strategy == "find shelter" &&
            score.score == 95
        ) {
            shelter = true;
        }

        if (
            score.strategy == "keep distance" &&
            score.score == 70
        ) {
            distance = true;
        }

        if (
            score.strategy == "walk into storm" &&
            score.score == -90
        ) {
            storm = true;
        }
    }

    if (!shelter) {
        return EXIT_FAILURE;
    }

    if (!distance) {
        return EXIT_FAILURE;
    }

    if (!storm) {
        return EXIT_FAILURE;
    }

    const auto best =
        petoron_ai::select_best_strategy(
            scores
        );

    if (best.strategy != "find shelter") {
        return EXIT_FAILURE;
    }

    if (best.score != 95) {
        return EXIT_FAILURE;
    }

    const auto empty_best =
        petoron_ai::select_best_strategy({});

    if (!empty_best.strategy.empty()) {
        return EXIT_FAILURE;
    }

    if (empty_best.score != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
