/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_ucb_selection.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace petoron_ai {

bool try_select_ucb_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type,
    double exploration_weight,
    std::size_t& selected_index
) {
    if (statistics.size() == 0) {
        return false;
    }

    if (exploration_weight < 0.0) {
        exploration_weight = 0.0;
    }

    std::size_t total_observations = 0;
    bool found = false;

    for (std::size_t i = 0; i < statistics.size(); ++i) {
        const auto& entry = statistics.at(i);

        if (entry.goal_type != goal_type) {
            continue;
        }

        found = true;

        total_observations +=
            entry.success_count +
            entry.failure_count;
    }

    if (!found) {
        return false;
    }

    double best_score =
        -std::numeric_limits<double>::infinity();

    for (std::size_t i = 0; i < statistics.size(); ++i) {
        const auto& entry = statistics.at(i);

        if (entry.goal_type != goal_type) {
            continue;
        }

        const auto observations =
            entry.success_count +
            entry.failure_count;

        const double mean =
            static_cast<double>(entry.success_count + 1) /
            static_cast<double>(observations + 2);

        const double exploration =
            exploration_weight *
            std::sqrt(
                std::log(static_cast<double>(total_observations + 1)) /
                static_cast<double>(observations + 1)
            );

        const double score =
            mean + exploration;

        if (score > best_score) {
            best_score = score;
            selected_index = i;
        }
    }

    return true;
}

const GoalPolicyStatistic& select_ucb_policy_for_goal(
    const GoalPolicyStatistics& statistics,
    const std::string& goal_type,
    double exploration_weight
) {
    std::size_t selected_index = 0;

    if (
        !try_select_ucb_policy_for_goal(
            statistics,
            goal_type,
            exploration_weight,
            selected_index
        )
    ) {
        throw std::out_of_range("no policy for goal_type");
    }

    return statistics.at(selected_index);
}

}
