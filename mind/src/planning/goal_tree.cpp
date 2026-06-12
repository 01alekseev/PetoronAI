/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/goal_tree.hpp"

namespace petoron_ai {

GoalNode build_goal_tree(
    const std::string& goal
) {
    GoalNode root;
    root.goal = goal;

    if (goal == "avoid storm") {
        root.subgoals.push_back({"find shelter", {}});
        root.subgoals.push_back({"secure shelter", {}});
        root.subgoals.push_back({"stay protected", {}});
    }

    if (goal == "avoid fire") {
        root.subgoals.push_back({"leave fire area", {}});
        root.subgoals.push_back({"keep safe distance", {}});
        root.subgoals.push_back({"avoid smoke", {}});
    }

    if (goal == "avoid injury") {
        root.subgoals.push_back({"stabilize body", {}});
        root.subgoals.push_back({"move carefully", {}});
        root.subgoals.push_back({"avoid impact", {}});
    }

    return root;
}

}
