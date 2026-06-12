/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/thought/thought_search.hpp"
#include "petoron_ai/thought/thought_store_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: petoron_ai_find_thought <store.pts> <source_goal>\n";
        return 1;
    }

    petoron_ai::ThoughtStore store;

    if (!petoron_ai::read_thought_store_file(argv[1], store)) {
        return 2;
    }

    const auto thoughts =
        petoron_ai::find_thoughts_by_goal(
            store,
            argv[2]
        );

    std::cout << "matches: " << thoughts.size() << "\n";

    const auto* best =
        petoron_ai::best_thought_for_goal(
            store,
            argv[2]
        );

    if (best == nullptr) {
        std::cout << "best: none\n";
        return 0;
    }

    std::cout << "best_thought: " << best->thought << "\n";
    std::cout << "reason: " << best->reason << "\n";
    std::cout << "confidence: " << best->confidence << "\n";

    std::cout << "thought_id: ";
    petoron_ai_app::print_digest(best->id);
    std::cout << "\n";

    return 0;
}
