/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/state/mind_state_file.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"

#include <string>

namespace petoron_ai {

bool verify_mind_state_transition(
    const std::string& old_state_path,
    const std::string& transition_path,
    const std::string& new_state_path
);

}
