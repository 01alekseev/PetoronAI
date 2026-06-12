/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_evidence.hpp"

namespace petoron_ai {

double calculate_goal_policy_evidence(
    const GoalPolicyStatistic& statistic
) {
    const auto total =
        statistic.success_count +
        statistic.failure_count;

    constexpr double k = 10.0;

    return static_cast<double>(total) /
           (static_cast<double>(total) + k);
}

}
