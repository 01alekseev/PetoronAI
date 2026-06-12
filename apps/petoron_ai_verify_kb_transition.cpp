/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 6) {
        std::cerr << "usage: petoron_ai_verify_kb_transition <old.pkb> <input.paiin> <cycle.pcycle> <new.pkb> <transition.pkbt>\n";
        return 1;
    }

    if (!petoron_ai::verify_knowledge_transition_file(
        argv[1],
        argv[2],
        argv[3],
        argv[4],
        argv[5]
    )) {
        std::cerr << "transition verify failed\n";
        return 2;
    }

    petoron_ai::KnowledgeTransitionFile file;

    if (!petoron_ai::read_knowledge_transition_file(argv[5], file)) {
        std::cerr << "transition read failed\n";
        return 3;
    }

    const auto transition_id =
        petoron_ai::commit_knowledge_transition_file(file);

    std::cout << "PetoronAI kb transition verify PASS\n";

    std::cout << "transition_id: ";
    petoron_ai_app::print_digest(transition_id);
    std::cout << "\n";

    return 0;
}
