/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/runtime_input_codec.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: petoron_ai_run_cycle <input.paiin> <output.pcycle>\n";
        return 1;
    }

    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_runtime_input(argv[1], input)) {
        std::cerr << "input read failed\n";
        return 2;
    }

    const auto input_id =
        petoron_ai::commit_runtime_input(input);

    petoron_ai::PetoronMind mind;

    for (const auto& observation : input.observations) {
        mind.observe(observation);
    }

    const auto start_root = mind.root();

    const auto result =
        petoron_ai::run_cycle(
            mind,
            input.goal,
            input.rules
        );

    const auto trace =
        petoron_ai::build_agent_cycle_trace(
            input_id,
            petoron_ai::MemoryDigest{},
            start_root,
            input.goal,
            result
        );

    if (!petoron_ai::write_cycle_file(argv[2], trace)) {
        std::cerr << "write failed\n";
        return 3;
    }

    std::cout << "cycle written\n";
    return 0;
}
