/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_confidence.hpp"

namespace petoron_ai {

double calculate_goal_policy_confidence(
    const GoalPolicyStatistic& statistic
) {
    const auto total =
        statistic.success_count +
        statistic.failure_count;

    if (total == 0) {
        return 0.0;
    }

    return static_cast<double>(
        statistic.success_count
    ) / static_cast<double>(total);
}

}
