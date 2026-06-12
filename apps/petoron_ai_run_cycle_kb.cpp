/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/knowledge/knowledge_mind_bridge.hpp"
#include "petoron_ai/runtime_input_codec.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: petoron_ai_run_cycle_kb <knowledge.pkb> <input.paiin> <output.pcycle>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore store;

    if (!petoron_ai::read_knowledge_file(argv[1], store)) {
        std::cerr << "kb read failed\n";
        return 2;
    }

    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_runtime_input(argv[2], input)) {
        std::cerr << "input read failed\n";
        return 3;
    }

    const auto input_id =
        petoron_ai::commit_runtime_input(input);

    const auto kb_id =
        store.root();

    petoron_ai::PetoronMind mind;
    petoron_ai::load_knowledge_into_mind(store, mind);

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
            kb_id,
            start_root,
            input.goal,
            result
        );

    if (!petoron_ai::write_cycle_file(argv[3], trace)) {
        std::cerr << "write failed\n";
        return 4;
    }

    std::cout << "cycle written\n";
    return 0;
}
