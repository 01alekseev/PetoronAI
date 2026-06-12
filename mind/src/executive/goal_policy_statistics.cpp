/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_statistics.hpp"

namespace petoron_ai {

void GoalPolicyStatistics::add(
    const GoalPolicyStatistic& statistic
) {
    statistics_.push_back(statistic);
}

std::size_t GoalPolicyStatistics::size() const {
    return statistics_.size();
}

const GoalPolicyStatistic&
GoalPolicyStatistics::at(
    std::size_t index
) const {
    return statistics_.at(index);
}

}
