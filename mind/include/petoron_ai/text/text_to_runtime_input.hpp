/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/runtime_input.hpp"

#include <string>

namespace petoron_ai {

RuntimeInput text_to_runtime_input(
    const std::string& text
);

}
