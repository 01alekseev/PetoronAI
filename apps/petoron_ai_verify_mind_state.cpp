/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/state/mind_state_file.hpp"
#include "petoron_ai/state/mind_state_verifier.hpp"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "usage: petoron_ai_verify_mind_state <current.pkb> <state.pms> <transition.pkbt> [...]\n";
        return 1;
    }

    std::vector<std::string> transitions;

    for (int i = 3; i < argc; ++i) {
        transitions.push_back(argv[i]);
    }

    if (!petoron_ai::verify_mind_state(
        argv[1],
        argv[2],
        transitions
    )) {
        std::cerr << "mind state verify failed\n";
        return 2;
    }

    petoron_ai::MindState state;

    if (!petoron_ai::read_mind_state_file(argv[2], state)) {
        std::cerr << "mind state read failed\n";
        return 3;
    }

    const auto state_id =
        petoron_ai::commit_mind_state(state);

    std::cout << "PetoronAI mind state verify PASS\n";

    std::cout << "state_id: ";
    petoron_ai_app::print_digest(state_id);
    std::cout << "\n";

    std::cout << "current_kb_id: ";
    petoron_ai_app::print_digest(state.current_kb_id);
    std::cout << "\n";

    std::cout << "transition_chain_id: ";
    petoron_ai_app::print_digest(state.transition_chain_id);
    std::cout << "\n";

    std::cout << "last_cycle_id: ";
    petoron_ai_app::print_digest(state.last_cycle_id);
    std::cout << "\n";

    std::cout << "cycle_count: " << state.cycle_count << "\n";

    return 0;
}
