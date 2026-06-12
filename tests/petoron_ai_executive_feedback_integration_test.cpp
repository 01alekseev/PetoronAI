/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_feedback_integration.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutiveAnalytics analytics;

    analytics.learning_count = 1;
    analytics.recovering_count = 1;

    ExecutiveFeedback positive;
    positive.positive = true;

    const auto positive_result =
        integrate_executive_feedback(
            analytics,
            positive
        );

    if (positive_result.learning_count != 2) {
        return EXIT_FAILURE;
    }

    ExecutiveFeedback negative;
    negative.negative = true;

    const auto negative_result =
        integrate_executive_feedback(
            analytics,
            negative
        );

    if (negative_result.recovering_count != 2) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
