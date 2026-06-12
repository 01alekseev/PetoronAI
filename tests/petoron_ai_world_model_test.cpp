/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_model.hpp"

#include <cstdlib>

int main() {
    petoron_ai::WorldModel model =
        petoron_ai::make_world_model({
            {"storm", "causes", "damage", 90},
            {"storm", "requires", "shelter", 95},
            {"fire", "causes", "burn", 90}
        });

    const auto model2 =
        petoron_ai::make_world_model({
            {"storm", "causes", "damage", 90},
            {"storm", "requires", "shelter", 95},
            {"fire", "causes", "burn", 90}
        });

    if (model.id != model2.id) {
        return EXIT_FAILURE;
    }

    const auto storm =
        petoron_ai::find_world_relations(
            model,
            "storm"
        );

    if (storm.size() != 2) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::add_world_relation(
        model,
        {"fire", "requires", "distance", 95}
    )) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::add_world_relation(
        model,
        {"fire", "requires", "distance", 95}
    )) {
        return EXIT_FAILURE;
    }

    const auto fire =
        petoron_ai::find_world_relations(
            model,
            "fire"
        );

    if (fire.size() != 2) {
        return EXIT_FAILURE;
    }

    if (model.id == model2.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
