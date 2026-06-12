/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/planner.hpp"

namespace petoron_ai {

static std::string action_for_goal(
    const std::string& goal
) {
    if (goal == "find shelter") {
        return "search for shelter";
    }

    if (goal == "secure shelter") {
        return "secure shelter entrance";
    }

    if (goal == "stay protected") {
        return "stay inside shelter";
    }

    if (goal == "leave fire area") {
        return "move away from fire";
    }

    if (goal == "keep safe distance") {
        return "keep safe distance";
    }

    if (goal == "avoid smoke") {
        return "avoid smoke exposure";
    }

    if (goal == "stabilize body") {
        return "stabilize body";
    }

    if (goal == "move carefully") {
        return "move carefully";
    }

    if (goal == "avoid impact") {
        return "avoid impact";
    }

    return goal;
}

std::vector<PlanStep> build_plan(
    const GoalNode& tree
) {
    std::vector<PlanStep> plan;

    if (tree.subgoals.empty()) {
        plan.push_back({
            tree.goal,
            action_for_goal(tree.goal)
        });

        return plan;
    }

    for (const auto& subgoal : tree.subgoals) {
        plan.push_back({
            subgoal.goal,
            action_for_goal(subgoal.goal)
        });
    }

    return plan;
}

}
