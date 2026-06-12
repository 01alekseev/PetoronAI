/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/cycle_file.hpp"

#include "common/hex.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_verify_cycle <file.pcycle>\n";
        return 1;
    }

    petoron_ai::CycleFile file;

    if (!petoron_ai::read_cycle_file(argv[1], file)) {
        std::cerr << "read failed\n";
        return 2;
    }

    if (!petoron_ai::verify_cycle_file(file)) {
        std::cerr << "cycle verify failed\n";
        return 3;
    }

    std::cout << "PetoronAI cycle verify PASS\n";
    std::cout << "goal: " << file.trace.goal_name << "\n";

    std::cout << "cycle_id: ";
    petoron_ai_app::print_digest(file.cycle_id);
    std::cout << "\n";

    std::cout << "final_root: ";
    petoron_ai_app::print_digest(file.final_root);
    std::cout << "\n";

    return 0;
}
