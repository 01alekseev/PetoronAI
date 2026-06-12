/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/state/mind_state_transition_verifier.hpp"

namespace petoron_ai {

bool verify_mind_state_transition(
    const std::string& old_state_path,
    const std::string& transition_path,
    const std::string& new_state_path
) {
    MindState old_state;

    if (!read_mind_state_file(old_state_path, old_state)) {
        return false;
    }

    KnowledgeTransitionFile transition;

    if (!read_knowledge_transition_file(transition_path, transition)) {
        return false;
    }

    MindState new_state;

    if (!read_mind_state_file(new_state_path, new_state)) {
        return false;
    }

    if (old_state.current_kb_id != transition.old_kb_id) {
        return false;
    }

    if (new_state.current_kb_id != transition.new_kb_id) {
        return false;
    }

    if (new_state.last_cycle_id != transition.cycle_id) {
        return false;
    }

    if (new_state.cycle_count != old_state.cycle_count + 1) {
        return false;
    }

    return true;
}

}
