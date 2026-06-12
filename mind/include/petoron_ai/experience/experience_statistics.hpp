/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/knowledge/knowledge_store.hpp"

#include <string>

namespace petoron_ai {

struct ExperienceStatistics {
    int experience_count = 0;
    int success_count = 0;
    int failure_count = 0;
    int success_rate = 0;
    int average_reward = 0;
};

ExperienceStatistics experience_statistics(
    const KnowledgeStore& kb,
    const std::string& goal
);

}
