/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "usage: petoron_ai_verify_kb_transition_chain <a.pkbt> <b.pkbt> [...]\n";
        return 1;
    }

    std::vector<petoron_ai::KnowledgeTransitionFile> files;

    for (int i = 1; i < argc; ++i) {
        petoron_ai::KnowledgeTransitionFile file;

        if (!petoron_ai::read_knowledge_transition_file(argv[i], file)) {
            std::cerr << "transition invalid\n";
            return 2;
        }

        files.push_back(file);
    }

    for (std::size_t i = 1; i < files.size(); ++i) {
        if (files[i - 1].new_kb_id != files[i].old_kb_id) {
            std::cerr << "transition chain mismatch\n";
            return 3;
        }
    }

    const auto chain_id = petoron_ai::commit_knowledge_transition_chain(files);

    std::cout << "PetoronAI kb transition chain verify PASS\n";
    std::cout << "transitions: " << files.size() << "\n";

    std::cout << "chain_id: ";
    petoron_ai_app::print_digest(chain_id);
    std::cout << "\n";

    std::cout << "start_kb_id: ";
    petoron_ai_app::print_digest(files.front().old_kb_id);
    std::cout << "\n";

    std::cout << "final_kb_id: ";
    petoron_ai_app::print_digest(files.back().new_kb_id);
    std::cout << "\n";

    return 0;
}
