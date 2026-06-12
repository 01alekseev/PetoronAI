/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_inspect_kb_transition <file.pkbt>\n";
        return 1;
    }

    petoron_ai::KnowledgeTransitionFile file;

    if (!petoron_ai::read_knowledge_transition_file(argv[1], file)) {
        std::cerr << "transition invalid\n";
        return 2;
    }

    const auto transition_id =
        petoron_ai::commit_knowledge_transition_file(file);

    std::cout << "PetoronAI knowledge transition\n";
    std::cout << "valid: true\n";

    std::cout << "transition_id: ";
    petoron_ai_app::print_digest(transition_id);
    std::cout << "\n";

    std::cout << "old_kb_id: ";
    petoron_ai_app::print_digest(file.old_kb_id);
    std::cout << "\n";

    std::cout << "input_id: ";
    petoron_ai_app::print_digest(file.input_id);
    std::cout << "\n";

    std::cout << "cycle_id: ";
    petoron_ai_app::print_digest(file.cycle_id);
    std::cout << "\n";

    std::cout << "feedback_commitment: ";
    petoron_ai_app::print_digest(file.feedback_commitment);
    std::cout << "\n";

    std::cout << "new_kb_id: ";
    petoron_ai_app::print_digest(file.new_kb_id);
    std::cout << "\n";

    return 0;
}
