/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory/long_term_memory.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct Context {
    std::vector<std::string> facts;
};

Context build_context(
    const std::vector<MemoryItem>& memories
);

}
