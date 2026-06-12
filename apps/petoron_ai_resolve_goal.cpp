/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

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

    const auto goal =
        petoron_ai::resolve_goal(
            kb,
            input
        );

    std::cout
        << "resolved_goal: "
        << goal
        << "\n";

    return 0;
}
