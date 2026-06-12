/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_confidence.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistic statistic;

    statistic.goal_type = "exploration";
    statistic.policy_id = "policy_a";

    statistic.success_count = 8;
    statistic.failure_count = 2;

    const double confidence =
        calculate_goal_policy_confidence(
            statistic
        );

    if (confidence < 0.79) {
        return EXIT_FAILURE;
    }

    if (confidence > 0.81) {
        return EXIT_FAILURE;
    }

    GoalPolicyStatistic empty;

    if (
        calculate_goal_policy_confidence(
            empty
        ) != 0.0
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
