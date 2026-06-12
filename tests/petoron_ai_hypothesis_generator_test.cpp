/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning/hypothesis_generator.hpp"

#include <algorithm>
#include <cstdlib>

int main() {
    const auto storm =
        petoron_ai::generate_hypotheses(
            {
                "storm exists",
                "shelter reduces risk"
            }
        );

    if (storm.size() != 3) {
        return EXIT_FAILURE;
    }

    if (storm[0] != "find shelter") {
        return EXIT_FAILURE;
    }

    if (
        std::find(
            storm.begin(),
            storm.end(),
            "leave area"
        ) == storm.end()
    ) {
        return EXIT_FAILURE;
    }

    const auto generic =
        petoron_ai::generate_hypotheses(
            {
                "unknown situation"
            }
        );

    if (generic.size() != 1) {
        return EXIT_FAILURE;
    }

    if (generic[0] != "gather more information") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
