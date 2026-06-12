/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <cstddef>

namespace petoron_ai {

struct ExecutiveFeedback {
    bool positive = false;
    bool negative = false;

    std::size_t positive_weight = 0;
    std::size_t negative_weight = 0;
};

ExecutiveFeedback evaluate_executive_feedback(
    int successful_executions,
    int failed_executions
);

}
