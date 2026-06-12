/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/runtime_input_codec.hpp"

#include "common/hex.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: petoron_ai_verify_cycle_input <input.paiin> <file.pcycle>\n";
        return 1;
    }

    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_runtime_input(argv[1], input)) {
        std::cerr << "input invalid\n";
        return 2;
    }

    petoron_ai::CycleFile file;

    if (!petoron_ai::read_cycle_file(argv[2], file)) {
        std::cerr << "cycle read failed\n";
        return 3;
    }

    if (!petoron_ai::verify_cycle_file(file)) {
        std::cerr << "cycle invalid\n";
        return 4;
    }

    const auto input_id =
        petoron_ai::commit_runtime_input(input);

    if (input_id != file.trace.input_id) {
        std::cerr << "input_id mismatch\n";
        return 5;
    }

    std::cout << "PetoronAI cycle input verify PASS\n";

    std::cout << "input_id: ";
    petoron_ai_app::print_digest(input_id);
    std::cout << "\n";

    std::cout << "cycle_id: ";
    petoron_ai_app::print_digest(file.cycle_id);
    std::cout << "\n";

    std::cout << "final_root: ";
    petoron_ai_app::print_digest(file.final_root);
    std::cout << "\n";

    return 0;
}
