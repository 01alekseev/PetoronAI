/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_chain.hpp"

#include <cstdlib>
#include <vector>

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
            "storm requires shelter",
            "storm is dangerous",
            "avoid storm",
            90
        );

    const auto c =
        petoron_ai::make_thought_artifact(
            "stay inside shelter",
            "shelter reduces exposure",
            "avoid storm",
            100
        );

    const auto chain =
        petoron_ai::make_thought_chain({a, b, c});

    const auto chain2 =
        petoron_ai::make_thought_chain({a, b, c});

    const auto other =
        petoron_ai::make_thought_chain({a, c});

    if (chain.steps.size() != 3) {
        return EXIT_FAILURE;
    }

    if (chain.id != chain2.id) {
        return EXIT_FAILURE;
    }

    if (chain.id == other.id) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::thought_chain_confidence(chain) != 90) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
