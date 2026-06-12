/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>

namespace petoron_ai {

struct CounterfactualComparison {
    std::string actual_action;
    int actual_risk = 0;

    std::string alternative_action;
    int alternative_risk = 0;

    std::string preferred_action;
};

CounterfactualComparison compare_futures(
    const std::string& actual_action,
    int actual_risk,
    const std::string& alternative_action,
    int alternative_risk
);

}
