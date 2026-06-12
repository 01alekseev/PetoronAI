/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_evolution.hpp"

namespace petoron_ai {

StrategyArtifact evolve_strategy(
    const StrategyArtifact& a,
    const StrategyArtifact& b,
    const std::string& evolved_goal,
    const std::string& evolved_action
) {
    ThoughtPath path;
    path.found = a.path.found && b.path.found;
    path.score = (a.score + b.score) / 2;

    for (const auto& node : a.path.nodes) {
        path.nodes.push_back(node);
    }

    for (const auto& node : b.path.nodes) {
        path.nodes.push_back(node);
    }

    return make_strategy_artifact(
        evolved_goal,
        path,
        evolved_action
    );
}

}
