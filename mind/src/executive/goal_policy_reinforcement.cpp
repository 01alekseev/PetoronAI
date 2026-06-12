/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_reinforcement.hpp"

namespace petoron_ai {

void reinforce_goal_policy(
    GoalPolicyStatistic& statistic,
    const ExecutiveFeedback& feedback
) {
    if (feedback.positive) {
        statistic.success_count +=
            feedback.positive_weight == 0
                ? 1
                : feedback.positive_weight;
    }

    if (feedback.negative) {
        statistic.failure_count +=
            feedback.negative_weight == 0
                ? 1
                : feedback.negative_weight;
    }
}

}
