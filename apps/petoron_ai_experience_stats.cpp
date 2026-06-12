/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/experience/experience_statistics.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: petoron_ai_experience_stats <world.pkb> <goal>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore kb;

    if (!petoron_ai::read_knowledge_file(argv[1], kb)) {
        return 2;
    }

    const auto stats =
        petoron_ai::experience_statistics(
            kb,
            argv[2]
        );

    std::cout << "goal: " << argv[2] << "\n";
    std::cout << "experience_count: " << stats.experience_count << "\n";
    std::cout << "success_count: " << stats.success_count << "\n";
    std::cout << "failure_count: " << stats.failure_count << "\n";
    std::cout << "success_rate: " << stats.success_rate << "\n";
    std::cout << "average_reward: " << stats.average_reward << "\n";

    return 0;
}
