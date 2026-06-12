/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_feedback.hpp"

namespace petoron_ai {

ExecutiveFeedback evaluate_executive_feedback(
    int successful_executions,
    int failed_executions
) {
    ExecutiveFeedback result;

    if (successful_executions > failed_executions) {
        result.positive = true;
        result.positive_weight =
            static_cast<std::size_t>(
                successful_executions - failed_executions
            );
    }

    if (failed_executions > successful_executions) {
        result.negative = true;
        result.negative_weight =
            static_cast<std::size_t>(
                failed_executions - successful_executions
            );
    }

    return result;
}

}
