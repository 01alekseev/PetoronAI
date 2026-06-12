/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

struct ExecutiveSafetyState {
    int survival = 0;
    int safety = 0;
    int resources = 0;
    int knowledge = 0;
    int risk = 0;
};

bool is_policy_safe(
    const ExecutiveSafetyState& state,
    const std::string& policy_id
);

}
