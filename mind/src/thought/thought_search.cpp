/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_search.hpp"

namespace petoron_ai {

std::vector<ThoughtArtifact> find_thoughts_by_goal(
    const ThoughtStore& store,
    const std::string& source_goal
) {
    std::vector<ThoughtArtifact> out;

    for (const auto& item : store.thoughts) {
        if (item.source_goal == source_goal) {
            out.push_back(item);
        }
    }

    return out;
}

const ThoughtArtifact* best_thought_for_goal(
    const ThoughtStore& store,
    const std::string& source_goal
) {
    const ThoughtArtifact* best = nullptr;

    for (const auto& item : store.thoughts) {
        if (item.source_goal != source_goal) {
            continue;
        }

        if (best == nullptr || item.confidence > best->confidence) {
            best = &item;
        }
    }

    return best;
}

}
