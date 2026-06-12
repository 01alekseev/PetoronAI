/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_store.hpp"

#include <cstdlib>

static petoron_ai::StrategyArtifact make_strategy(
    const std::string& goal,
    int first_weight,
    int second_weight,
    const std::string& action
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

    const auto c =
        petoron_ai::make_thought_artifact(
            action + " complete",
            "complete reason",
            goal,
            100
        );

    const auto graph =
        petoron_ai::make_thought_graph(
            {a, b, c},
            {
                {a.id, b.id, first_weight},
                {b.id, c.id, second_weight}
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

    const auto weak =
        make_strategy(
            "avoid storm",
            30,
            20,
            "wait"
        );

    const auto strong =
        make_strategy(
            "avoid storm",
            90,
            100,
            "find shelter"
        );

    const auto fire =
        make_strategy(
            "avoid fire",
            80,
            80,
            "move away"
        );

    if (!petoron_ai::add_strategy(store, weak)) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::add_strategy(store, strong)) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::add_strategy(store, fire)) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::add_strategy(store, strong)) {
        return EXIT_FAILURE;
    }

    const auto* best =
        petoron_ai::best_strategy_for_goal(
            store,
            "avoid storm"
        );

    if (best == nullptr) {
        return EXIT_FAILURE;
    }

    if (best->action != "find shelter") {
        return EXIT_FAILURE;
    }

    if (best->score != 190) {
        return EXIT_FAILURE;
    }

    const auto* missing =
        petoron_ai::best_strategy_for_goal(
            store,
            "avoid injury"
        );

    if (missing != nullptr) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
