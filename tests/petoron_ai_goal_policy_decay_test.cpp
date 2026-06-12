/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_decay.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistic statistic;

    statistic.goal_type = "exploration";
    statistic.policy_id = "policy_a";

    statistic.success_count = 5;
    statistic.failure_count = 3;

    decay_goal_policy(
        statistic
    );

    if (statistic.success_count != 4) {
        return EXIT_FAILURE;
    }

    if (statistic.failure_count != 2) {
        return EXIT_FAILURE;
    }

    decay_goal_policy(statistic);
    decay_goal_policy(statistic);
    decay_goal_policy(statistic);

    if (statistic.failure_count != 0) {
        return EXIT_FAILURE;
    }

    decay_goal_policy(statistic);

    if (statistic.failure_count != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
