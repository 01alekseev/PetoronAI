/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct GoalNode {
    std::string goal;
    std::vector<GoalNode> subgoals;
};

GoalNode build_goal_tree(
    const std::string& goal
);

}
