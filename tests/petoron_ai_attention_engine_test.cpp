/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/attention_engine.hpp"
#include "petoron_ai/memory/long_term_memory.hpp"

#include <cstdlib>

int main() {
    petoron_ai::LongTermMemory memory;

    petoron_ai::remember_fact(
        memory,
        "storm is dangerous",
        50
    );

    petoron_ai::remember_fact(
        memory,
        "food exists",
        10
    );

    petoron_ai::remember_fact(
        memory,
        "shelter reduces risk",
        100
    );

    const auto top2 =
        petoron_ai::select_attention_memories(
            memory,
            2
        );

    if (top2.size() != 2) {
        return EXIT_FAILURE;
    }

    if (top2[0].fact != "shelter reduces risk") {
        return EXIT_FAILURE;
    }

    if (top2[1].fact != "storm is dangerous") {
        return EXIT_FAILURE;
    }

    const auto top1 =
        petoron_ai::select_attention_memories(
            memory,
            1
        );

    if (top1.size() != 1) {
        return EXIT_FAILURE;
    }

    if (top1[0].fact != "shelter reduces risk") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
