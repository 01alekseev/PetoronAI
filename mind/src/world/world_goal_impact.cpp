/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_goal_impact.hpp"

namespace petoron_ai {

static bool is_negative_object(
    const std::string& value
) {
    return
        value == "danger" ||
        value == "injury" ||
        value == "damage" ||
        value == "burn";
}

static bool is_positive_object(
    const std::string& value
) {
    return
        value == "shelter" ||
        value == "protection" ||
        value == "distance" ||
        value == "safety";
}

static bool is_safety_goal(
    const std::string& value
) {
    return
        value == "stay safe" ||
        value == "avoid danger" ||
        value == "avoid injury";
}

std::vector<GoalImpact> evaluate_goal_impact(
    const WorldModel& model,
    const Goal& goal
) {
    std::vector<GoalImpact> out;

    if (!is_safety_goal(goal.name)) {
        return out;
    }

    for (const auto& relation : model.relations) {
        GoalImpact impact;
        impact.subject = relation.subject;
        impact.relation = relation.relation;
        impact.object = relation.object;
        impact.goal = goal.name;

        if (is_negative_object(relation.object)) {
            impact.impact_score = -relation.confidence;
            impact.positive = false;
            out.push_back(impact);
            continue;
        }

        if (is_positive_object(relation.object)) {
            impact.impact_score = relation.confidence;
            impact.positive = true;
            out.push_back(impact);
            continue;
        }
    }

    return out;
}

}
