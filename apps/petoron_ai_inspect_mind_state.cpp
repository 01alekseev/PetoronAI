/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/state/mind_state_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_inspect_mind_state <file.pms>\n";
        return 1;
    }

    petoron_ai::MindState state;

    if (!petoron_ai::read_mind_state_file(argv[1], state)) {
        std::cerr << "mind state invalid\n";
        return 2;
    }

    const auto state_id =
        petoron_ai::commit_mind_state(state);

    std::cout << "PetoronAI mind state\n";
    std::cout << "valid: true\n";

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
