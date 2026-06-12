/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/state/mind_state.hpp"

#include <string>

namespace petoron_ai {

bool write_mind_state_file(
    const std::string& path,
    const MindState& state
);

bool read_mind_state_file(
    const std::string& path,
    MindState& state
);

}
