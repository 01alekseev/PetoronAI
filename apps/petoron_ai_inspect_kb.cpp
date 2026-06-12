/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_inspect_kb <file.pkb>\n";
        return 1;
    }

    petoron_ai::KnowledgeStore store;

    if (!petoron_ai::read_knowledge_file(argv[1], store)) {
        std::cerr << "kb invalid\n";
        return 2;
    }

    std::cout << "PetoronAI knowledge base\n";
    std::cout << "valid: true\n";
    std::cout << "facts: " << store.facts().size() << "\n";

    std::size_t relation_count = 0;
    for (const auto& fact : store.facts()) {
        relation_count += store.relations_from(fact).size();
    }

    std::cout << "relations: " << relation_count << "\n";

    std::cout << "root: ";
    petoron_ai_app::print_digest(store.root());
    std::cout << "\n";

    return 0;
}
