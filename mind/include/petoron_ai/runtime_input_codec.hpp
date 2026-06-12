/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/runtime_input.hpp"

#include <cstdint>
#include <vector>

namespace petoron_ai {

std::vector<std::uint8_t> encode_runtime_input(
    const RuntimeInput& input
);

MemoryDigest commit_runtime_input(
    const RuntimeInput& input
);

}
