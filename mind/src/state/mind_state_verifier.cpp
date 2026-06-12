/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/state/mind_state_verifier.hpp"

namespace petoron_ai {

static bool is_zero_digest(
    const MemoryDigest& digest
) {
    for (const auto byte : digest) {
        if (byte != 0) {
            return false;
        }
    }

    return true;
}

bool verify_mind_state(
    const std::string& current_kb_path,
    const std::string& state_path,
    const std::vector<std::string>& transition_paths
) {
    KnowledgeStore store;

    if (!read_knowledge_file(current_kb_path, store)) {
        return false;
    }

    MindState state;

    if (!read_mind_state_file(state_path, state)) {
        return false;
    }

    if (transition_paths.empty()) {
        return false;
    }

    std::vector<KnowledgeTransitionFile> transitions;

    for (const auto& path : transition_paths) {
        KnowledgeTransitionFile transition;

        if (!read_knowledge_transition_file(path, transition)) {
            return false;
        }

        transitions.push_back(transition);
    }

    for (std::size_t i = 1; i < transitions.size(); ++i) {
        if (transitions[i - 1].new_kb_id != transitions[i].old_kb_id) {
            return false;
        }
    }

    const auto current_kb_id = store.root();
    const auto chain_id =
        commit_knowledge_transition_chain(transitions);

    if (state.current_kb_id != current_kb_id) {
        return false;
    }

    if (state.transition_chain_id != chain_id) {
        return false;
    }

    if (state.last_cycle_id != transitions.back().cycle_id) {
        return false;
    }

    if (state.cycle_count != transitions.size()) {
        return false;
    }

    if (state.cycle_count == 0) {
        return false;
    }

    if (is_zero_digest(state.current_kb_id)) {
        return false;
    }

    if (is_zero_digest(state.transition_chain_id)) {
        return false;
    }

    if (is_zero_digest(state.last_cycle_id)) {
        return false;
    }

    return true;
}

}
