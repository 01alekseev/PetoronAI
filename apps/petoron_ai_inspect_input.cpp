/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime_input_codec.hpp"

#include "common/hex.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_inspect_input <input.paiin>\n";
        return 1;
    }

    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_runtime_input(argv[1], input)) {
        std::cerr << "input invalid\n";
        return 2;
    }

    const auto input_id =
        petoron_ai::commit_runtime_input(input);

    std::cout << "PetoronAI input\n";
    std::cout << "valid: true\n";
    std::cout << "goal: " << input.goal.name << "\n";
    std::cout << "goal_candidates: " << input.goal_candidates.size() << "\n";

    for (const auto& candidate : input.goal_candidates) {
        std::cout << "goal_candidate: " << candidate.name << "\n";
    }

    std::cout << "observations: " << input.observations.size() << "\n";
    std::cout << "rules: " << input.rules.size() << "\n";

    std::cout << "input_id: ";
    petoron_ai_app::print_digest(input_id);
    std::cout << "\n";

    return 0;
}
