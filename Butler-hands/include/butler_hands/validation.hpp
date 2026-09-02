/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "butler_hands/types.hpp"

#include <string>

namespace butler_hands {

void validate_snapshot(const EnvironmentSnapshot& snapshot);
void validate_config(const RuntimeConfig& config);
void validate_execution_result(const ExecutionResult& result);

}
