/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/runtime_input_codec.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: petoron_ai_verify_cycle_kb_input <knowledge.pkb> <input.paiin> <file.pcycle>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore store;

    if (!petoron_ai::read_knowledge_file(argv[1], store)) {
        std::cerr << "kb invalid\n";
        return 2;
    }

    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_runtime_input(argv[2], input)) {
        std::cerr << "input invalid\n";
        return 3;
    }

    petoron_ai::CycleFile file;

    if (!petoron_ai::read_cycle_file(argv[3], file)) {
        std::cerr << "cycle read failed\n";
        return 4;
    }

    if (!petoron_ai::verify_cycle_file(file)) {
        std::cerr << "cycle invalid\n";
        return 5;
    }

    const auto kb_id = store.root();
    const auto input_id =
        petoron_ai::commit_runtime_input(input);

    if (kb_id != file.trace.kb_id) {
        std::cerr << "kb_id mismatch\n";
        return 6;
    }

    if (input_id != file.trace.input_id) {
        std::cerr << "input_id mismatch\n";
        return 7;
    }

    std::cout << "PetoronAI cycle kb input verify PASS\n";

    std::cout << "kb_id: ";
    petoron_ai_app::print_digest(kb_id);
    std::cout << "\n";

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
