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
        std::cerr << "usage: petoron_ai_inspect_cycle <file.pcycle>\n";
        return 1;
    }

    petoron_ai::CycleFile file;

    if (!petoron_ai::read_cycle_file(argv[1], file)) {
        std::cerr << "read failed\n";
        return 2;
    }

    std::cout << "PetoronAI cycle\n";
    std::cout << "goal: " << file.trace.goal_name << "\n";
    std::cout << "feedback_count: " << file.trace.feedback_count << "\n";

    std::cout << "cycle_id: ";
    petoron_ai_app::print_digest(file.cycle_id);
    std::cout << "\n";

    std::cout << "kb_id: ";
    petoron_ai_app::print_digest(file.trace.kb_id);
    std::cout << "\n";

    std::cout << "input_id: ";
    petoron_ai_app::print_digest(file.trace.input_id);
    std::cout << "\n";

    std::cout << "start_root: ";
    petoron_ai_app::print_digest(file.trace.start_root);
    std::cout << "\n";

    std::cout << "final_root: ";
    petoron_ai_app::print_digest(file.final_root);
    std::cout << "\n";

    std::cout << "plan_commitment: ";
    petoron_ai_app::print_digest(file.trace.plan_commitment);
    std::cout << "\n";

    std::cout << "actions_commitment: ";
    petoron_ai_app::print_digest(file.trace.actions_commitment);
    std::cout << "\n";

    std::cout << "feedback_commitment: ";
    petoron_ai_app::print_digest(file.trace.feedback_commitment);
    std::cout << "\n";

    std::cout << "valid: "
              << (petoron_ai::verify_cycle_file(file) ? "true" : "false")
              << "\n";

    return 0;
}
