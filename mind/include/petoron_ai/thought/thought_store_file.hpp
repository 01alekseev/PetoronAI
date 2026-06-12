/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/thought/thought_store.hpp"

#include <string>

namespace petoron_ai {

bool write_thought_store_file(
    const std::string& path,
    const ThoughtStore& store
);

bool read_thought_store_file(
    const std::string& path,
    ThoughtStore& store
);

}
