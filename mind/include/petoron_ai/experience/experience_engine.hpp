/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/experience/experience_record.hpp"
#include "petoron_ai/knowledge/knowledge_store.hpp"

namespace petoron_ai {

void apply_experience(
    KnowledgeStore& kb,
    const ExperienceRecord& record
);

}
