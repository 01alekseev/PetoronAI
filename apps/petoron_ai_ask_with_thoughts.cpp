/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/future_simulator.hpp"
#include "petoron_ai/goal_resolver.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/meta/meta_reasoning_artifact.hpp"
#include "petoron_ai/strategy/strategy_artifact.hpp"
#include "petoron_ai/text/text_to_runtime_input.hpp"
#include "petoron_ai/thought/thought_graph.hpp"
#include "petoron_ai/thought/thought_search.hpp"
#include "petoron_ai/thought/thought_store_file.hpp"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: petoron_ai_ask_with_thoughts <kb.pkb> <thoughts.pts> <text>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore kb;
    petoron_ai::ThoughtStore thoughts;

    if (!petoron_ai::read_knowledge_file(argv[1], kb)) {
        return 2;
    }

    if (!petoron_ai::read_thought_store_file(argv[2], thoughts)) {
        return 3;
    }

    const auto input =
        petoron_ai::text_to_runtime_input(argv[3]);

    const auto resolution =
        petoron_ai::resolve_goal_trace(kb, input);

    const auto* best_thought =
        petoron_ai::best_thought_for_goal(
            thoughts,
            resolution.resolved_goal
        );

    const auto outcomes =
        petoron_ai::simulate_goal(resolution);

    const petoron_ai::FutureOutcome* selected = nullptr;

    for (const auto& outcome : outcomes) {
        if (selected == nullptr || outcome.risk_score < selected->risk_score) {
            selected = &outcome;
        }
    }

    std::cout << "Goal: " << resolution.resolved_goal << "\n";

    if (best_thought == nullptr) {
        std::cout << "Thought: none\n";
    } else {
        std::cout << "Thought: " << best_thought->thought << "\n";
        std::cout << "Thought reason: " << best_thought->reason << "\n";
        std::cout << "Thought confidence: " << best_thought->confidence << "\n";
    }

    if (selected == nullptr) {
        std::cout << "No simulated action available\n";
        return 0;
    }

    petoron_ai::ThoughtPath path;

    if (best_thought != nullptr) {
        path.nodes.push_back(best_thought->id);
        path.score = best_thought->confidence;
        path.found = true;
    }

    const auto strategy =
        petoron_ai::make_strategy_artifact(
            resolution.resolved_goal,
            path,
            selected->action
        );

    const auto meta =
        petoron_ai::make_meta_reasoning_artifact(
            strategy
        );

    std::cout << "Selected action: " << selected->action << "\n";
    std::cout << "Expected future: " << selected->future_state << "\n";
    std::cout << "Risk: " << selected->risk_score << "\n";
    std::cout << "Meta explanation: " << meta.explanation << "\n";
    std::cout << "Meta confidence: " << meta.confidence << "\n";

    return 0;
}
