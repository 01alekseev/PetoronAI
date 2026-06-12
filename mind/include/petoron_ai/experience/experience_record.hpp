/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

struct ExperienceRecord {
    std::string goal;
    std::string action;
    int predicted_risk = 0;
    std::string actual_result;
    int reward = 0;
};

}
