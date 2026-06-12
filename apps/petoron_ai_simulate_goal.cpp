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
        petoron_ai::resolve_goal_trace(
            kb,
            input
        );

    const auto outcomes =
        petoron_ai::simulate_goal(resolution);

    std::cout << "goal: "
              << resolution.resolved_goal
              << "\n";

    std::string selected_action;
    std::string selected_future;
    int selected_risk = 0;
    bool has_selected = false;

    for (const auto& outcome : outcomes) {
        std::cout << "candidate_action: "
                  << outcome.action
                  << "\n";

        std::cout << "future_state: "
                  << outcome.future_state
                  << "\n";

        std::cout << "risk_score: "
                  << outcome.risk_score
                  << "\n";

        if (!has_selected || outcome.risk_score < selected_risk) {
            has_selected = true;
            selected_action = outcome.action;
            selected_future = outcome.future_state;
            selected_risk = outcome.risk_score;
        }
    }

    if (has_selected) {
        std::cout << "selected_action: "
                  << selected_action
                  << "\n";

        std::cout << "selected_future: "
                  << selected_future
                  << "\n";

        std::cout << "selected_risk: "
                  << selected_risk
                  << "\n";
    }

    return 0;
}
