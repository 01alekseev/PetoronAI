/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_node.hpp"

#include <iostream>

namespace petoron_ai_app {

inline void print_digest(
    const petoron_ai::MemoryDigest& digest
) {
    for (const auto byte : digest) {
        const char* hex = "0123456789abcdef";
        std::cout << hex[(byte >> 4) & 0x0f];
        std::cout << hex[byte & 0x0f];
    }
}

}
