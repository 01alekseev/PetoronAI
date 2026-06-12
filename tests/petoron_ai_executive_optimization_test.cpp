/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_optimization.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutiveAnalytics analytics;

    analytics.planning_count = 1;
    analytics.executing_count = 5;

    analytics.recovering_count = 4;
    analytics.learning_count = 1;

    const auto result =
        optimize_executive_cycle(
            analytics
        );

    if (!result.increase_planning) {
        return EXIT_FAILURE;
    }

    if (!result.reduce_recovery) {
        return EXIT_FAILURE;
    }

    ExecutiveAnalytics healthy;

    healthy.planning_count = 5;
    healthy.executing_count = 3;

    healthy.recovering_count = 1;
    healthy.learning_count = 4;

    const auto healthy_result =
        optimize_executive_cycle(
            healthy
        );

    if (healthy_result.increase_planning) {
        return EXIT_FAILURE;
    }

    if (healthy_result.reduce_recovery) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
