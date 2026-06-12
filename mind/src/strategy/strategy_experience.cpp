/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_experience.hpp"

namespace petoron_ai {

static MemoryDigest commit_strategy_experience(
    const MemoryDigest& strategy_id,
    int success_count,
    int failure_count,
    int reward_total
) {
    MemoryGraph graph;

    MemoryNode strategy_node;
    strategy_node.type = "strategy_experience_strategy";
    strategy_node.payload = std::to_string(strategy_id[0]);
    graph.nodes.push_back(strategy_node);

    MemoryNode success_node;
    success_node.type = "strategy_experience_success";
    success_node.payload = std::to_string(success_count);
    graph.nodes.push_back(success_node);

    MemoryNode failure_node;
    failure_node.type = "strategy_experience_failure";
    failure_node.payload = std::to_string(failure_count);
    graph.nodes.push_back(failure_node);

    MemoryNode reward_node;
    reward_node.type = "strategy_experience_reward";
    reward_node.payload = std::to_string(reward_total);
    graph.nodes.push_back(reward_node);

    return commit_memory_graph(graph);
}

StrategyExperience make_strategy_experience(
    const StrategyArtifact& strategy,
    bool success,
    int reward
) {
    StrategyExperience experience;
    experience.strategy_id = strategy.id;
    experience.success_count = success ? 1 : 0;
    experience.failure_count = success ? 0 : 1;
    experience.reward_total = reward;
    experience.id =
        commit_strategy_experience(
            experience.strategy_id,
            experience.success_count,
            experience.failure_count,
            experience.reward_total
        );

    return experience;
}

StrategyExperience merge_strategy_experience(
    const StrategyExperience& a,
    const StrategyExperience& b
) {
    StrategyExperience out;
    out.strategy_id = a.strategy_id;
    out.success_count = a.success_count + b.success_count;
    out.failure_count = a.failure_count + b.failure_count;
    out.reward_total = a.reward_total + b.reward_total;
    out.id =
        commit_strategy_experience(
            out.strategy_id,
            out.success_count,
            out.failure_count,
            out.reward_total
        );

    return out;
}

int strategy_success_rate(
    const StrategyExperience& experience
) {
    const int total =
        experience.success_count + experience.failure_count;

    if (total == 0) {
        return 0;
    }

    return (experience.success_count * 100) / total;
}

}
