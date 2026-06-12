/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_store_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_inspect_thought_store <store.pts>\n";
        return 1;
    }

    petoron_ai::ThoughtStore store;

    if (!petoron_ai::read_thought_store_file(argv[1], store)) {
        return 2;
    }

    std::cout << "thoughts: " << store.thoughts.size() << "\n";

    for (const auto& item : store.thoughts) {
        std::cout << "thought: " << item.thought << "\n";
        std::cout << "reason: " << item.reason << "\n";
        std::cout << "source_goal: " << item.source_goal << "\n";
        std::cout << "confidence: " << item.confidence << "\n";
    }

    return 0;
}
