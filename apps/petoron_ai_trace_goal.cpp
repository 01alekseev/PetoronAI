/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal_resolver.hpp"
#include "petoron_ai/runtime_input.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }

    petoron_ai::KnowledgeStore kb;
    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_knowledge_file(argv[1], kb)) {
        return 2;
    }

    if (!petoron_ai::read_runtime_input(argv[2], input)) {
        return 3;
    }

    const auto resolution =
        petoron_ai::resolve_goal_trace(
            kb,
            input
        );

    for (const auto& candidate : resolution.candidates) {
        std::cout << "candidate: " << candidate.goal << "\n";
        std::cout << "reason: " << candidate.reason << "\n";
        std::cout << "base: " << candidate.base << "\n";
        std::cout << "confidence: " << candidate.confidence << "\n";
        std::cout << "strategy: " << candidate.strategy << "\n";
        std::cout << "experience: " << candidate.experience << "\n";
        std::cout << "score: " << candidate.score << "\n";
    }

    std::cout << "resolved_goal: "
              << resolution.resolved_goal
              << "\n";

    std::cout << "resolved_reason: "
              << resolution.resolved_reason
              << "\n";

    std::cout << "resolved_score: "
              << resolution.resolved_score
              << "\n";

    return 0;
}
