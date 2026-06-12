/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_evolution.hpp"

#include <cstdlib>

static petoron_ai::StrategyArtifact make_base_strategy(
    const std::string& goal,
    const std::string& action,
    int weight
) {
    const auto a =
        petoron_ai::make_thought_artifact(
            goal + " start",
            "start reason",
            goal,
            80
        );

    const auto b =
        petoron_ai::make_thought_artifact(
            action,
            "action reason",
            goal,
            90
        );

    const auto graph =
        petoron_ai::make_thought_graph(
            {a, b},
            {
                {a.id, b.id, weight}
            }
        );

    const auto path =
        petoron_ai::best_thought_path(
            graph,
            a.id
        );

    return petoron_ai::make_strategy_artifact(
        goal,
        path,
        action
    );
}

int main() {
    const auto storm =
        make_base_strategy(
            "avoid storm",
            "find shelter",
            100
        );

    const auto fire =
        make_base_strategy(
            "avoid fire",
            "increase distance",
            80
        );

    const auto evolved =
        petoron_ai::evolve_strategy(
            storm,
            fire,
            "avoid danger",
            "increase protection from danger source"
        );

    const auto evolved2 =
        petoron_ai::evolve_strategy(
            storm,
            fire,
            "avoid danger",
            "increase protection from danger source"
        );

    if (!evolved.path.found) {
        return EXIT_FAILURE;
    }

    if (evolved.goal != "avoid danger") {
        return EXIT_FAILURE;
    }

    if (evolved.action != "increase protection from danger source") {
        return EXIT_FAILURE;
    }

    if (evolved.score != 90) {
        return EXIT_FAILURE;
    }

    if (evolved.path.nodes.size() != 4) {
        return EXIT_FAILURE;
    }

    if (evolved.id != evolved2.id) {
        return EXIT_FAILURE;
    }

    if (evolved.id == storm.id) {
        return EXIT_FAILURE;
    }

    if (evolved.id == fire.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
