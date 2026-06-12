/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/cycle_file.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct KnowledgeTransitionFile {
    MemoryDigest old_kb_id;
    MemoryDigest input_id;
    MemoryDigest cycle_id;
    MemoryDigest feedback_commitment;
    MemoryDigest new_kb_id;
};

bool write_knowledge_transition_file(
    const std::string& path,
    const KnowledgeTransitionFile& file
);

bool read_knowledge_transition_file(
    const std::string& path,
    KnowledgeTransitionFile& file
);

MemoryDigest commit_knowledge_transition_file(
    const KnowledgeTransitionFile& file
);

MemoryDigest commit_knowledge_transition_chain(
    const std::vector<KnowledgeTransitionFile>& files
);

bool verify_knowledge_transition_file(
    const std::string& old_kb_path,
    const std::string& input_path,
    const std::string& cycle_path,
    const std::string& new_kb_path,
    const std::string& transition_path
);

}
