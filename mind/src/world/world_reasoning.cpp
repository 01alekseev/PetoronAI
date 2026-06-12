/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_reasoning.hpp"

namespace petoron_ai {

static bool same_relation(
    const WorldRelation& a,
    const WorldRelation& b
) {
    return
        a.subject == b.subject &&
        a.relation == b.relation &&
        a.object == b.object;
}

static bool contains_relation(
    const std::vector<WorldRelation>& relations,
    const WorldRelation& relation
) {
    for (const auto& item : relations) {
        if (same_relation(item, relation)) {
            return true;
        }
    }

    return false;
}

std::vector<WorldRelation> infer_world_relations(
    const WorldModel& model
) {
    std::vector<WorldRelation> inferred;

    for (const auto& left : model.relations) {
        for (const auto& right : model.relations) {
            if (left.relation != right.relation) {
                continue;
            }

            if (left.object != right.subject) {
                continue;
            }

            WorldRelation relation;
            relation.subject = left.subject;
            relation.relation = left.relation;
            relation.object = right.object;
            relation.confidence =
                left.confidence < right.confidence
                    ? left.confidence
                    : right.confidence;

            if (contains_relation(model.relations, relation)) {
                continue;
            }

            if (contains_relation(inferred, relation)) {
                continue;
            }

            inferred.push_back(relation);
        }
    }

    return inferred;
}

}
