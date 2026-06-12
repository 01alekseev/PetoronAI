/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/state/mind_state_file.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

bool verify_mind_state(
    const std::string& current_kb_path,
    const std::string& state_path,
    const std::vector<std::string>& transition_paths
);

}
