/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/experience/experience_engine.hpp"
#include "petoron_ai/experience/experience_file.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: petoron_ai_record_experience <old.pkb> <experience.pexp> <new.pkb>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore kb;
    petoron_ai::ExperienceRecord record;

    if (!petoron_ai::read_knowledge_file(argv[1], kb)) {
        return 2;
    }

    if (!petoron_ai::read_experience_file(argv[2], record)) {
        return 3;
    }

    petoron_ai::apply_experience(kb, record);

    if (!petoron_ai::write_knowledge_file(argv[3], kb)) {
        return 4;
    }

    std::cout << "PetoronAI experience recorded\n";

    return 0;
}
