/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/state/mind_state_transition_verifier.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: petoron_ai_verify_mind_state_transition <old.pms> <transition.pkbt> <new.pms>\n";
        return 1;
    }

    if (!petoron_ai::verify_mind_state_transition(
        argv[1],
        argv[2],
        argv[3]
    )) {
        std::cerr << "mind state transition verify failed\n";
        return 2;
    }

    std::cout << "PetoronAI mind state transition verify PASS\n";
    return 0;
}
