/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_evidence.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistic small;

    small.success_count = 1;
    small.failure_count = 0;

    GoalPolicyStatistic large;

    large.success_count = 100;
    large.failure_count = 0;

    const double small_evidence =
        calculate_goal_policy_evidence(
            small
        );

    const double large_evidence =
        calculate_goal_policy_evidence(
            large
        );

    if (!(large_evidence > small_evidence)) {
        return EXIT_FAILURE;
    }

    if (!(small_evidence > 0.0)) {
        return EXIT_FAILURE;
    }

    if (!(large_evidence < 1.0)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
