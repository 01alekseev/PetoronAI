/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/future_simulator.hpp"
#include "petoron_ai/goal_resolver.hpp"
#include "petoron_ai/runtime_input.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }

    petoron_ai::KnowledgeStore kb;
    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_knowledge_file(argv[1], kb)) {
        return 2;
    }

    if (!petoron_ai::read_runtime_input(argv[2], input)) {
        return 3;
    }

    const auto resolution =
        petoron_ai::resolve_goal_trace(kb, input);

    const auto outcomes =
        petoron_ai::simulate_goal(resolution);

    std::cout << "Goal: " << resolution.resolved_goal << "\n";

    const petoron_ai::FutureOutcome* selected = nullptr;

    for (const auto& outcome : outcomes) {
        if (selected == nullptr || outcome.risk_score < selected->risk_score) {
            selected = &outcome;
        }
    }

    if (selected == nullptr) {
        std::cout << "No simulated action available\n";
        return 0;
    }

    std::cout << "Selected action: " << selected->action << "\n";
    std::cout << "Expected future: " << selected->future_state << "\n";
    std::cout << "Risk: " << selected->risk_score << "\n";

    for (const auto& outcome : outcomes) {
        if (&outcome == selected) {
            continue;
        }

        std::cout << "Rejected action: " << outcome.action << "\n";
        std::cout << "Rejected future: " << outcome.future_state << "\n";
        std::cout << "Rejected risk: " << outcome.risk_score << "\n";
    }

    return 0;
}
