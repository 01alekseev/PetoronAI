/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_feedback_integration.hpp"

namespace petoron_ai {

ExecutiveAnalytics integrate_executive_feedback(
    const ExecutiveAnalytics& analytics,
    const ExecutiveFeedback& feedback
) {
    ExecutiveAnalytics result = analytics;

    if (feedback.positive) {
        ++result.learning_count;
    }

    if (feedback.negative) {
        ++result.recovering_count;
    }

    return result;
}

}
