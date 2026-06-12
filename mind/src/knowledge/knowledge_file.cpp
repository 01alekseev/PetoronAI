/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/knowledge/knowledge_file.hpp"

#include <fstream>
#include <sstream>

namespace petoron_ai {

bool write_knowledge_file(
    const std::string& path,
    const KnowledgeStore& store
) {
    std::ofstream out(path);

    if (!out) {
        return false;
    }

    out << "PKB:1\n";

    for (const auto& fact : store.facts()) {
        out << "fact:" << fact << "\n";
    }

    for (const auto& fact : store.facts()) {
        const auto relations =
            store.relations_from(fact);

        for (const auto& relation : relations) {
            out << "relation:"
                << relation.type << "|"
                << relation.from << "|"
                << relation.to << "\n";
        }
    }

    return static_cast<bool>(out);
}

bool read_knowledge_file(
    const std::string& path,
    KnowledgeStore& store
) {
    store = KnowledgeStore{};

    std::ifstream in(path);

    if (!in) {
        return false;
    }

    std::string line;

    if (!std::getline(in, line)) {
        return false;
    }

    if (line != "PKB:1") {
        return false;
    }

    while (std::getline(in, line)) {
        if (line.empty()) {
            return false;
        }

        if (line.rfind("fact:", 0) == 0) {
            const auto fact = line.substr(5);

            if (!store.add_fact(fact)) {
                return false;
            }

            continue;
        }

        if (line.rfind("relation:", 0) == 0) {
            std::stringstream ss(line.substr(9));

            std::string type;
            std::string from;
            std::string to;
            std::string extra;

            if (!std::getline(ss, type, '|')) {
                return false;
            }

            if (!std::getline(ss, from, '|')) {
                return false;
            }

            if (!std::getline(ss, to, '|')) {
                return false;
            }

            if (std::getline(ss, extra, '|')) {
                return false;
            }

            KnowledgeRelation relation;
            relation.type = type;
            relation.from = from;
            relation.to = to;

            if (!store.add_relation(relation)) {
                return false;
            }

            continue;
        }

        return false;
    }

    return true;
}

}
