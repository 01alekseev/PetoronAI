/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/world/world_goal_impact.hpp"

#include <cstdlib>

int main() {
    const auto model =
        petoron_ai::make_world_model({
            {"storm", "causes", "danger", 90},
            {"storm", "requires", "shelter", 95},
            {"fire", "causes", "injury", 80},
            {"fire", "requires", "distance", 70}
        });

    petoron_ai::Goal goal;
    goal.name = "stay safe";

    const auto impacts =
        petoron_ai::evaluate_goal_impact(
            model,
            goal
        );

    bool storm_danger = false;
    bool storm_shelter = false;
    bool fire_injury = false;
    bool fire_distance = false;

    for (const auto& impact : impacts) {
        if (
            impact.subject == "storm" &&
            impact.object == "danger" &&
            impact.impact_score == -90 &&
            !impact.positive
        ) {
            storm_danger = true;
        }

        if (
            impact.subject == "storm" &&
            impact.object == "shelter" &&
            impact.impact_score == 95 &&
            impact.positive
        ) {
            storm_shelter = true;
        }

        if (
            impact.subject == "fire" &&
            impact.object == "injury" &&
            impact.impact_score == -80 &&
            !impact.positive
        ) {
            fire_injury = true;
        }

        if (
            impact.subject == "fire" &&
            impact.object == "distance" &&
            impact.impact_score == 70 &&
            impact.positive
        ) {
            fire_distance = true;
        }
    }

    if (impacts.size() != 4) {
        return EXIT_FAILURE;
    }

    if (!storm_danger) {
        return EXIT_FAILURE;
    }

    if (!storm_shelter) {
        return EXIT_FAILURE;
    }

    if (!fire_injury) {
        return EXIT_FAILURE;
    }

    if (!fire_distance) {
        return EXIT_FAILURE;
    }

    petoron_ai::Goal unknown_goal;
    unknown_goal.name = "collect resources";

    const auto none =
        petoron_ai::evaluate_goal_impact(
            model,
            unknown_goal
        );

    if (!none.empty()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
