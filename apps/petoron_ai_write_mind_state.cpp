/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"
#include "petoron_ai/state/mind_state_file.hpp"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "usage: petoron_ai_write_mind_state <current.pkb> <output.pms> <transition.pkbt> [...]\n";
        return 1;
    }

    petoron_ai::KnowledgeStore store;

    if (!petoron_ai::read_knowledge_file(argv[1], store)) {
        std::cerr << "kb invalid\n";
        return 2;
    }

    std::vector<petoron_ai::KnowledgeTransitionFile> transitions;

    for (int i = 3; i < argc; ++i) {
        petoron_ai::KnowledgeTransitionFile transition;

        if (!petoron_ai::read_knowledge_transition_file(argv[i], transition)) {
            std::cerr << "transition invalid\n";
            return 3;
        }

        transitions.push_back(transition);
    }

    for (std::size_t i = 1; i < transitions.size(); ++i) {
        if (transitions[i - 1].new_kb_id != transitions[i].old_kb_id) {
            std::cerr << "transition chain mismatch\n";
            return 4;
        }
    }

    if (transitions.empty()) {
        std::cerr << "empty transition chain\n";
        return 5;
    }

    const auto current_kb_id = store.root();

    if (current_kb_id != transitions.back().new_kb_id) {
        std::cerr << "current kb mismatch\n";
        return 6;
    }

    petoron_ai::MindState state;
    state.current_kb_id = current_kb_id;
    state.transition_chain_id =
        petoron_ai::commit_knowledge_transition_chain(transitions);
    state.last_cycle_id = transitions.back().cycle_id;
    state.cycle_count = transitions.size();

    if (!petoron_ai::write_mind_state_file(argv[2], state)) {
        std::cerr << "state write failed\n";
        return 7;
    }

    std::cout << "mind state written\n";
    return 0;
}
