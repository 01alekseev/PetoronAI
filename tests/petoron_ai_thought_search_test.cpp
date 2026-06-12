/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_search.hpp"

#include <cstdlib>

int main() {
    petoron_ai::ThoughtStore store;

    const auto low =
        petoron_ai::make_thought_artifact(
            "storm requires awareness",
            "storm is dangerous",
            "avoid storm",
            40
        );

    const auto high =
        petoron_ai::make_thought_artifact(
            "storm requires shelter",
            "shelter reduces exposure",
            "avoid storm",
            90
        );

    const auto other =
        petoron_ai::make_thought_artifact(
            "fire requires distance",
            "fire is dangerous",
            "avoid fire",
            80
        );

    petoron_ai::add_thought(store, low);
    petoron_ai::add_thought(store, high);
    petoron_ai::add_thought(store, other);

    const auto storm =
        petoron_ai::find_thoughts_by_goal(
            store,
            "avoid storm"
        );

    if (storm.size() != 2) {
        return EXIT_FAILURE;
    }

    const auto* best =
        petoron_ai::best_thought_for_goal(
            store,
            "avoid storm"
        );

    if (best == nullptr) {
        return EXIT_FAILURE;
    }

    if (best->thought != "storm requires shelter") {
        return EXIT_FAILURE;
    }

    if (best->confidence != 90) {
        return EXIT_FAILURE;
    }

    const auto* missing =
        petoron_ai::best_thought_for_goal(
            store,
            "avoid injury"
        );

    if (missing != nullptr) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
