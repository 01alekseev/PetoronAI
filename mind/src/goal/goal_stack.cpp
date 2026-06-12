/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_stack.hpp"

#include <algorithm>
#include <utility>
#include <vector>

namespace petoron_ai {

std::vector<std::string> build_goal_stack(
    const GoalAdaptationState& state
) {
    std::vector<std::pair<std::string, int>> ranked;

    for (const auto& [goal, priority] : state.goal_priority) {
        ranked.push_back({goal, priority});
    }

    std::sort(
        ranked.begin(),
        ranked.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    std::vector<std::string> result;

    for (const auto& item : ranked) {
        result.push_back(item.first);
    }

    return result;
}

}
