/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_switching.hpp"
#include "petoron_ai/strategy/strategy_portfolio.hpp"

#include <cstdlib>

int main() {
    if (
        !petoron_ai::should_switch_strategy(
            50,
            100
        )
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::should_switch_strategy(
            100,
            50
        )
    ) {
        return EXIT_FAILURE;
    }

    petoron_ai::RankedUtility current{
        {},
        80
    };

    petoron_ai::StrategyPortfolio portfolio;

    portfolio.primary.utility = 80;

    portfolio.support.push_back(
        {
            {},
            120
        }
    );

    const auto replacement =
        petoron_ai::select_replacement_strategy(
            current,
            portfolio
        );

    if (replacement.utility != 120) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
