/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal/goal_conflict_resolver.hpp"

namespace petoron_ai {

GoalConflict resolve_goal_conflict(
    const PrioritizedGoal& left,
    const PrioritizedGoal& right
) {
    GoalConflict result;

    if (left.priority >= right.priority) {
        result.winner = left.goal.name;
        result.loser = right.goal.name;
        return result;
    }

    result.winner = right.goal.name;
    result.loser = left.goal.name;

    return result;
}

}
