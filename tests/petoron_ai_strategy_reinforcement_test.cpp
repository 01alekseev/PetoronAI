/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_reinforcement.hpp"

#include <cstdlib>

int main() {
    const petoron_ai::StrategyScore shelter_score{
        "find shelter",
        95
    };

    const petoron_ai::StrategyOutcome shelter_success{
        "find shelter",
        true,
        10
    };

    const auto shelter =
        petoron_ai::reinforce_strategy(
            shelter_score,
            shelter_success
        );

    if (shelter.strategy != "find shelter") {
        return EXIT_FAILURE;
    }

    if (shelter.old_score != 95) {
        return EXIT_FAILURE;
    }

    if (shelter.new_score != 105) {
        return EXIT_FAILURE;
    }

    const petoron_ai::StrategyScore storm_score{
        "walk into storm",
        -90
    };

    const petoron_ai::StrategyOutcome storm_failure{
        "walk into storm",
        false,
        20
    };

    const auto storm =
        petoron_ai::reinforce_strategy(
            storm_score,
            storm_failure
        );

    if (storm.strategy != "walk into storm") {
        return EXIT_FAILURE;
    }

    if (storm.old_score != -90) {
        return EXIT_FAILURE;
    }

    if (storm.new_score != -110) {
        return EXIT_FAILURE;
    }

    const petoron_ai::StrategyOutcome mismatch{
        "keep distance",
        true,
        100
    };

    const auto unchanged =
        petoron_ai::reinforce_strategy(
            shelter_score,
            mismatch
        );

    if (unchanged.new_score != 95) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
