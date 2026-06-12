/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/reward_assessment.hpp"

#include <cstdlib>

int main() {
    const petoron_ai::RewardAssessment strategy_a{
        80,
        40,
        10
    };

    if (
        petoron_ai::effective_reward_score(
            strategy_a
        ) != 110
    ) {
        return EXIT_FAILURE;
    }

    const petoron_ai::RewardAssessment strategy_b{
        90,
        5,
        0
    };

    if (
        petoron_ai::effective_reward_score(
            strategy_b
        ) != 95
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::effective_reward_score(
            strategy_a
        ) <=
        petoron_ai::effective_reward_score(
            strategy_b
        )
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
