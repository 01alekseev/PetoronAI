/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/agent_cycle.hpp"

namespace petoron_ai {

AgentCycleResult run_cycle(
    PetoronMind& mind,
    const Goal& goal,
    const std::vector<ReasoningRule>& rules
) {
    mind.autoreason(rules);

    AgentCycleResult result;
    result.plan = build_plan(mind, goal);
    result.actions = execute_plan(result.plan);
    result.feedback = learn_from_actions(
        mind,
        result.actions
    );
    result.final_root = mind.root();

    return result;
}

}
