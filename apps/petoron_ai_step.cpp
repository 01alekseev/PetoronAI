/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/knowledge/knowledge_feedback_delta.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/knowledge/knowledge_mind_bridge.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"
#include "petoron_ai/runtime_input_codec.hpp"
#include "petoron_ai/state/mind_state_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 8) {
        std::cerr << "usage: petoron_ai_step <old.pms> <old.pkb> <input.paiin> <new.pkb> <cycle.pcycle> <transition.pkbt> <new.pms>\n";
        return 1;
    }

    petoron_ai::MindState old_state;
    if (!petoron_ai::read_mind_state_file(argv[1], old_state)) {
        std::cerr << "old state invalid\n";
        return 2;
    }

    petoron_ai::KnowledgeStore store;
    if (!petoron_ai::read_knowledge_file(argv[2], store)) {
        std::cerr << "old kb invalid\n";
        return 3;
    }

    if (old_state.current_kb_id != store.root()) {
        std::cerr << "old state kb mismatch\n";
        return 4;
    }

    petoron_ai::RuntimeInput input;
    if (!petoron_ai::read_runtime_input(argv[3], input)) {
        std::cerr << "input invalid\n";
        return 5;
    }

    const auto input_id =
        petoron_ai::commit_runtime_input(input);

    const auto old_kb_id =
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
            old_kb_id,
            start_root,
            input.goal,
            result
        );

    if (!petoron_ai::write_cycle_file(argv[5], trace)) {
        std::cerr << "cycle write failed\n";
        return 6;
    }

    for (const auto& node : mind.graph().nodes) {
        store.add_fact(node.payload);
    }

    for (const auto& transition : result.feedback) {
        store.add_fact(transition.new_node.payload);
    }

    if (!petoron_ai::write_knowledge_file(argv[4], store)) {
        std::cerr << "new kb write failed\n";
        return 7;
    }

    petoron_ai::KnowledgeStore old_store;

    if (!petoron_ai::read_knowledge_file(argv[2], old_store)) {
        return 11;
    }

    petoron_ai::KnowledgeStore written_new_store;

    if (!petoron_ai::read_knowledge_file(argv[4], written_new_store)) {
        std::cerr << "new kb read failed\n";
        return 12;
    }

    petoron_ai::CycleFile written_cycle;

    if (!petoron_ai::read_cycle_file(argv[5], written_cycle)) {
        std::cerr << "cycle read failed\n";
        return 8;
    }

    petoron_ai::KnowledgeTransitionFile kt;
    kt.old_kb_id = old_kb_id;
    kt.input_id = input_id;
    kt.cycle_id = written_cycle.cycle_id;
    kt.feedback_commitment =
        petoron_ai::commit_knowledge_feedback_delta(
            old_store,
            written_new_store
        );
    kt.new_kb_id = written_new_store.root();

    if (!petoron_ai::write_knowledge_transition_file(argv[6], kt)) {
        std::cerr << "transition write failed\n";
        return 9;
    }

    petoron_ai::MindState new_state;
    new_state.current_kb_id = kt.new_kb_id;
    new_state.transition_chain_id =
        petoron_ai::commit_knowledge_transition_chain({kt});
    new_state.last_cycle_id = kt.cycle_id;
    new_state.cycle_count = old_state.cycle_count + 1;

    if (!petoron_ai::write_mind_state_file(argv[7], new_state)) {
        std::cerr << "new state write failed\n";
        return 10;
    }

    std::cout << "PetoronAI step PASS\n";
    return 0;
}
