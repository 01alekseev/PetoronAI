/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/long_term_memory.hpp"

#include <cstdlib>

int main() {
    petoron_ai::LongTermMemory memory;

    petoron_ai::remember_fact(
        memory,
        "storm is dangerous",
        10
    );

    petoron_ai::remember_fact(
        memory,
        "storm is dangerous",
        5
    );

    petoron_ai::remember_fact(
        memory,
        "shelter reduces risk",
        7
    );

    petoron_ai::remember_fact(
        memory,
        "",
        100
    );

    if (memory.items.size() != 2) {
        return EXIT_FAILURE;
    }

    const auto* storm =
        petoron_ai::find_memory_item(
            memory,
            "storm is dangerous"
        );

    if (storm == nullptr) {
        return EXIT_FAILURE;
    }

    if (storm->strength != 15) {
        return EXIT_FAILURE;
    }

    const auto* shelter =
        petoron_ai::find_memory_item(
            memory,
            "shelter reduces risk"
        );

    if (shelter == nullptr) {
        return EXIT_FAILURE;
    }

    if (shelter->strength != 7) {
        return EXIT_FAILURE;
    }

    const auto* missing =
        petoron_ai::find_memory_item(
            memory,
            "unknown"
        );

    if (missing != nullptr) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
