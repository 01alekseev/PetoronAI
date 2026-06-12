/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_reasoning.hpp"

#include <cstdlib>

int main() {
    const auto model =
        petoron_ai::make_world_model({
            {"storm", "causes", "damage", 90},
            {"damage", "causes", "danger", 80},
            {"fire", "causes", "burn", 90},
            {"burn", "causes", "injury", 70}
        });

    const auto inferred =
        petoron_ai::infer_world_relations(model);

    bool storm_danger = false;
    bool fire_injury = false;

    for (const auto& relation : inferred) {
        if (
            relation.subject == "storm" &&
            relation.relation == "causes" &&
            relation.object == "danger" &&
            relation.confidence == 80
        ) {
            storm_danger = true;
        }

        if (
            relation.subject == "fire" &&
            relation.relation == "causes" &&
            relation.object == "injury" &&
            relation.confidence == 70
        ) {
            fire_injury = true;
        }
    }

    if (!storm_danger) {
        return EXIT_FAILURE;
    }

    if (!fire_injury) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
