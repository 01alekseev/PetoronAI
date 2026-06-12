/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/memory_graph.hpp"

#include <string>
#include <vector>

namespace petoron_ai {

struct WorldRelation {
    std::string subject;
    std::string relation;
    std::string object;
    int confidence = 0;
};

struct WorldModel {
    std::vector<WorldRelation> relations;
    MemoryDigest id{};
};

WorldModel make_world_model(
    const std::vector<WorldRelation>& relations
);

bool add_world_relation(
    WorldModel& model,
    const WorldRelation& relation
);

std::vector<WorldRelation> find_world_relations(
    const WorldModel& model,
    const std::string& subject
);

}
