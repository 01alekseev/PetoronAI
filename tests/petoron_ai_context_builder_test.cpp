/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/context_builder.hpp"

#include <cstdlib>

int main() {
    const auto context =
        petoron_ai::build_context(
            {
                {"storm is dangerous", 100},
                {"shelter reduces risk", 90},
                {"food exists", 10}
            }
        );

    if (context.facts.size() != 3) {
        return EXIT_FAILURE;
    }

    if (context.facts[0] != "storm is dangerous") {
        return EXIT_FAILURE;
    }

    if (context.facts[1] != "shelter reduces risk") {
        return EXIT_FAILURE;
    }

    if (context.facts[2] != "food exists") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
