/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_planner.hpp"

#include <cstdlib>

static petoron_ai::StrategyArtifact make_strategy(
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
    petoron_ai::StrategyStore store;

    const auto high_score =
        make_strategy(
            "avoid storm",
            "run outside",
            120
        );

    const auto learned =
        make_strategy(
            "avoid storm",
            "find shelter",
            80
        );

    petoron_ai::add_strategy(store, high_score);
    petoron_ai::add_strategy(store, learned);

    const auto learned_success =
        petoron_ai::make_strategy_experience(
            learned,
            true,
            100
        );

    const auto plan =
        petoron_ai::plan_strategy(
            store,
            {learned_success},
            "avoid storm"
        );

    if (!plan.found) {
        return EXIT_FAILURE;
    }

    if (plan.selected_strategy.action != "find shelter") {
        return EXIT_FAILURE;
    }

    if (plan.expected_score != 80) {
        return EXIT_FAILURE;
    }

    if (plan.success_rate != 100) {
        return EXIT_FAILURE;
    }

    const auto missing =
        petoron_ai::plan_strategy(
            store,
            {learned_success},
            "avoid fire"
        );

    if (missing.found) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
