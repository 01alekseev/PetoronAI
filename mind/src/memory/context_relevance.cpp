/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/memory/context_relevance.hpp"

namespace petoron_ai {

std::vector<std::string> select_relevant_context(
    const Context& context,
    const std::string& goal
) {
    std::vector<std::string> result;

    for (const auto& fact : context.facts) {
        if (goal.find("storm") != std::string::npos) {
            if (fact.find("storm") != std::string::npos ||
                fact.find("shelter") != std::string::npos) {
                result.push_back(fact);
            }
            continue;
        }

        result.push_back(fact);
    }

    return result;
}

}
