/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/decision/decision_arena.hpp"

#include <cstdlib>
#include <vector>

int main() {
    using namespace petoron_ai;

    std::vector<DecisionCandidate> candidates = {
        {
            "collect resources",
            0,
            0,
            30,
            0,
            0
        },
        {
            "observe environment",
            0,
            0,
            0,
            30,
            10
        },
        {
            "secure shelter",
            10,
            35,
            0,
            0,
            20
        },
        {
            "reduce risk",
            20,
            25,
            0,
            0,
            40
        }
    };

    const auto result =
        run_decision_arena(
            candidates
        );

    if (result.selected_goal != "reduce risk") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
