/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/future_simulator.hpp"

namespace petoron_ai {

std::vector<FutureOutcome> simulate_goal(
    const GoalResolution& resolution
) {
    std::vector<FutureOutcome> out;

    if (resolution.resolved_goal == "avoid storm") {
        out.push_back({
            "find shelter",
            "safe shelter",
            10
        });

        out.push_back({
            "stay outside",
            "storm exposure",
            90
        });
    }

    if (resolution.resolved_goal == "avoid fire") {
        out.push_back({
            "leave area",
            "safe distance",
            10
        });

        out.push_back({
            "stay near fire",
            "burn risk",
            95
        });
    }

    if (resolution.resolved_goal == "avoid injury") {
        out.push_back({
            "stabilize body",
            "injury prevented",
            5
        });

        out.push_back({
            "ignore danger",
            "injury likely",
            90
        });
    }

    return out;
}

}
