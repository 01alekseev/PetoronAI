/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory/context_builder.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

std::vector<std::string> select_relevant_context(
    const Context& context,
    const std::string& goal
);

}
