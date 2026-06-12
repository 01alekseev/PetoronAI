/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/concept/concept_store.hpp"

#include <cstdlib>

int main() {
    petoron_ai::ConceptStore store;

    const auto danger =
        petoron_ai::make_concept_artifact(
            "danger",
            {"storm", "fire"},
            90,
            1
        );

    const auto danger2 =
        petoron_ai::make_concept_artifact(
            "danger",
            {"storm", "fire"},
            90,
            1
        );

    const auto threat =
        petoron_ai::make_concept_artifact(
            "threat",
            {"danger"},
            80,
            2
        );

    if (danger.name != "danger") {
        return EXIT_FAILURE;
    }

    if (danger.parents.size() != 2) {
        return EXIT_FAILURE;
    }

    if (danger.confidence != 90) {
        return EXIT_FAILURE;
    }

    if (danger.generation != 1) {
        return EXIT_FAILURE;
    }

    if (danger.id != danger2.id) {
        return EXIT_FAILURE;
    }

    if (danger.id == threat.id) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::add_concept(store, danger)) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::add_concept(store, danger)) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::add_concept(store, threat)) {
        return EXIT_FAILURE;
    }

    const auto* found =
        petoron_ai::find_concept(
            store,
            "danger"
        );

    if (found == nullptr) {
        return EXIT_FAILURE;
    }

    if (found->name != "danger") {
        return EXIT_FAILURE;
    }

    const auto* missing =
        petoron_ai::find_concept(
            store,
            "unknown"
        );

    if (missing != nullptr) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
