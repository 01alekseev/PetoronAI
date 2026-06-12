/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_decay.hpp"

namespace petoron_ai {

void decay_goal_policy(
    GoalPolicyStatistic& statistic
) {
    if (statistic.success_count > 0) {
        --statistic.success_count;
    }

    if (statistic.failure_count > 0) {
        --statistic.failure_count;
    }
}

}
