/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/context_relevance.hpp"

#include <cstdlib>

int main() {
    petoron_ai::Context context;

    context.facts.push_back("storm is dangerous");
    context.facts.push_back("shelter reduces risk");
    context.facts.push_back("food exists");

    const auto relevant =
        petoron_ai::select_relevant_context(
            context,
            "survive storm"
        );

    if (relevant.size() != 2) {
        return EXIT_FAILURE;
    }

    if (relevant[0] != "storm is dangerous") {
        return EXIT_FAILURE;
    }

    if (relevant[1] != "shelter reduces risk") {
        return EXIT_FAILURE;
    }

    const auto generic =
        petoron_ai::select_relevant_context(
            context,
            "general planning"
        );

    if (generic.size() != 3) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
