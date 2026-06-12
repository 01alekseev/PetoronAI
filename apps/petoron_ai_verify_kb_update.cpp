/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/knowledge/knowledge_feedback_delta.hpp"
#include "petoron_ai/runtime_input_codec.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "usage: petoron_ai_verify_kb_update <old.pkb> <input.paiin> <cycle.pcycle> <new.pkb>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore old_store;
    if (!petoron_ai::read_knowledge_file(argv[1], old_store)) {
        std::cerr << "old kb invalid\n";
        return 2;
    }

    petoron_ai::RuntimeInput input;
    if (!petoron_ai::read_runtime_input(argv[2], input)) {
        std::cerr << "input invalid\n";
        return 3;
    }

    petoron_ai::CycleFile cycle;
    if (!petoron_ai::read_cycle_file(argv[3], cycle)) {
        std::cerr << "cycle read failed\n";
        return 4;
    }

    if (!petoron_ai::verify_cycle_file(cycle)) {
        std::cerr << "cycle invalid\n";
        return 5;
    }

    petoron_ai::KnowledgeStore new_store;
    if (!petoron_ai::read_knowledge_file(argv[4], new_store)) {
        std::cerr << "new kb invalid\n";
        return 6;
    }

    const auto old_kb_id = old_store.root();
    const auto input_id = petoron_ai::commit_runtime_input(input);
    const auto new_kb_id = new_store.root();

    if (cycle.trace.kb_id != old_kb_id) {
        std::cerr << "old kb_id mismatch\n";
        return 7;
    }

    if (cycle.trace.input_id != input_id) {
        std::cerr << "input_id mismatch\n";
        return 8;
    }

    if (old_kb_id == new_kb_id) {
        std::cerr << "kb root did not change\n";
        return 9;
    }

    const auto feedback_commitment =
        petoron_ai::commit_knowledge_feedback_delta(
            old_store,
            new_store
        );

    if (feedback_commitment != cycle.trace.feedback_commitment) {
        std::cerr << "feedback commitment mismatch\n";
        return 10;
    }

    std::cout << "PetoronAI kb update verify PASS\n";

    std::cout << "old_kb_id: ";
    petoron_ai_app::print_digest(old_kb_id);
    std::cout << "\n";

    std::cout << "new_kb_id: ";
    petoron_ai_app::print_digest(new_kb_id);
    std::cout << "\n";

    std::cout << "cycle_id: ";
    petoron_ai_app::print_digest(cycle.cycle_id);
    std::cout << "\n";

    std::cout << "feedback_commitment: ";
    petoron_ai_app::print_digest(feedback_commitment);
    std::cout << "\n";

    return 0;
}
