/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/agent_cycle_trace.hpp"

#include <cstdint>
#include <vector>

namespace petoron_ai {

static void append_string(
    std::vector<std::uint8_t>& out,
    const std::string& value
) {
    const auto size =
        static_cast<std::uint64_t>(value.size());

    for (int i = 0; i < 8; ++i) {
        out.push_back(
            static_cast<std::uint8_t>(
                (size >> (i * 8)) & 0xff
            )
        );
    }

    out.insert(out.end(), value.begin(), value.end());
}

static MemoryDigest commit_plan(
    const Plan& plan
) {
    std::vector<std::uint8_t> bytes;

    append_string(bytes, plan.goal.name);

    for (const auto& step : plan.steps) {
        append_string(bytes, step.action);
        append_string(bytes, step.reason);
    }

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}


static MemoryDigest commit_feedback(
    const std::vector<MemoryTransition>& feedback
) {
    std::vector<std::uint8_t> bytes;

    for (const auto& transition : feedback) {
        append_string(bytes, "fact");
        append_string(bytes, transition.new_node.payload);
    }

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

static MemoryDigest commit_actions(
    const std::vector<ActionResult>& actions
) {
    std::vector<std::uint8_t> bytes;

    for (const auto& action : actions) {
        append_string(bytes, action.action);
        bytes.push_back(action.success ? 1 : 0);
        append_string(bytes, action.outcome);
    }

    return petoron::zk::PetoronZkCommitment::commit_bytes(bytes);
}

AgentCycleTrace build_agent_cycle_trace(
    const MemoryDigest& input_id,
    const MemoryDigest& kb_id,
    const MemoryDigest& start_root,
    const Goal& goal,
    const AgentCycleResult& result
) {
    AgentCycleTrace trace;
    trace.input_id = input_id;
    trace.kb_id = kb_id;
    trace.start_root = start_root;
    trace.final_root = result.final_root;
    trace.plan_commitment = commit_plan(result.plan);
    trace.actions_commitment = commit_actions(result.actions);
    trace.feedback_commitment = commit_feedback(result.feedback);
    trace.goal_name = goal.name;
    trace.feedback_count = result.feedback.size();
    return trace;
}

bool verify_agent_cycle_trace(
    const MemoryDigest& input_id,
    const MemoryDigest& kb_id,
    const MemoryDigest& start_root,
    const Goal& goal,
    const AgentCycleResult& result,
    const AgentCycleTrace& trace
) {
    if (trace.input_id != input_id) {
        return false;
    }

    if (trace.kb_id != kb_id) {
        return false;
    }

    if (trace.start_root != start_root) {
        return false;
    }

    if (trace.final_root != result.final_root) {
        return false;
    }

    if (trace.goal_name != goal.name) {
        return false;
    }

    if (trace.feedback_count != result.feedback.size()) {
        return false;
    }

    if (trace.feedback_commitment != commit_feedback(result.feedback)) {
        return false;
    }

    if (trace.plan_commitment != commit_plan(result.plan)) {
        return false;
    }

    return trace.actions_commitment == commit_actions(result.actions);
}

}
