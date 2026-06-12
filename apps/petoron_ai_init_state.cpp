/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/state/mind_state_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: petoron_ai_init_state <initial.pkb> <out.pms>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore store;

    if (!petoron_ai::read_knowledge_file(argv[1], store)) {
        std::cerr << "kb invalid\n";
        return 2;
    }

    petoron_ai::MindState state{};
    state.current_kb_id = store.root();
    state.cycle_count = 0;

    if (!petoron_ai::write_mind_state_file(argv[2], state)) {
        std::cerr << "state write failed\n";
        return 3;
    }

    std::cout << "mind state initialized\n";
    return 0;
}
