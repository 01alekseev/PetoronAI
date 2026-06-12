/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/knowledge/knowledge_feedback_delta.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"
#include "petoron_ai/runtime_input_codec.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 6) {
        std::cerr << "usage: petoron_ai_write_kb_transition <old.pkb> <input.paiin> <cycle.pcycle> <new.pkb> <out.pkbt>\n";
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
        std::cerr << "cycle invalid\n";
        return 4;
    }

    petoron_ai::KnowledgeStore new_store;
    if (!petoron_ai::read_knowledge_file(argv[4], new_store)) {
        std::cerr << "new kb invalid\n";
        return 5;
    }

    if (!petoron_ai::verify_cycle_file(cycle)) {
        std::cerr << "cycle verify failed\n";
        return 6;
    }

    petoron_ai::KnowledgeTransitionFile out;
    out.old_kb_id = old_store.root();
    out.input_id = petoron_ai::commit_runtime_input(input);
    out.cycle_id = cycle.cycle_id;
    out.feedback_commitment =
        petoron_ai::commit_knowledge_feedback_delta(
            old_store,
            new_store
        );
    out.new_kb_id = new_store.root();

    if (out.old_kb_id != cycle.trace.kb_id) {
        std::cerr << "old kb_id mismatch\n";
        return 7;
    }

    if (out.input_id != cycle.trace.input_id) {
        std::cerr << "input_id mismatch\n";
        return 8;
    }

    if (out.feedback_commitment != cycle.trace.feedback_commitment) {
        std::cerr << "feedback commitment mismatch\n";
        return 9;
    }

    if (!petoron_ai::write_knowledge_transition_file(argv[5], out)) {
        std::cerr << "transition write failed\n";
        return 10;
    }

    std::cout << "knowledge transition written\n";
    return 0;
}
