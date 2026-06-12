/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_reinforcement.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistic statistic;

    statistic.goal_type = "exploration";
    statistic.policy_id = "policy_a";

    statistic.success_count = 10;
    statistic.failure_count = 2;

    ExecutiveFeedback positive;
    positive.positive = true;

    reinforce_goal_policy(
        statistic,
        positive
    );

    if (statistic.success_count != 11) {
        return EXIT_FAILURE;
    }

    ExecutiveFeedback negative;
    negative.negative = true;

    reinforce_goal_policy(
        statistic,
        negative
    );

    if (statistic.failure_count != 3) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
