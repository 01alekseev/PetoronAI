/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_aware_policy_selection.hpp"

#include <stdexcept>

namespace petoron_ai {

bool try_select_best_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type,
    std::size_t& selected_index
) {
    double best_score = -1.0;
    bool found = false;

    for (std::size_t i = 0; i < statistics.size(); ++i) {
        const auto& entry = statistics.at(i);

        if (entry.goal_type != goal_type) {
            continue;
        }

        const auto total =
            entry.success_count +
            entry.failure_count;

        const double score =
            total == 0
            ? 0.0
            : static_cast<double>(entry.success_count) /
              static_cast<double>(total);

        if (!found || score > best_score) {
            found = true;
            best_score = score;
            selected_index = i;
        }
    }

    return found;
}

const GoalPolicyStatistic&
select_best_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type
) {
    std::size_t selected_index = 0;

    if (
        !try_select_best_policy_for_goal(
            statistics,
            goal_type,
            selected_index
        )
    ) {
        throw std::out_of_range("no policy for goal_type");
    }

    return statistics.at(selected_index);
}

}
