/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategy_portfolio.hpp"

#include <cstdlib>

int main() {
    std::vector<petoron_ai::RankedUtility> ranked{
        { {}, 120 },
        { {}, 100 },
        { {}, 90 },
        { {}, 70 }
    };

    const auto portfolio =
        petoron_ai::build_strategy_portfolio(
            ranked
        );

    if (portfolio.primary.utility != 120) {
        return EXIT_FAILURE;
    }

    if (portfolio.support.size() != 2) {
        return EXIT_FAILURE;
    }

    if (portfolio.support[0].utility != 100) {
        return EXIT_FAILURE;
    }

    if (portfolio.support[1].utility != 90) {
        return EXIT_FAILURE;
    }

    if (portfolio.reserve.size() != 1) {
        return EXIT_FAILURE;
    }

    if (portfolio.reserve[0].utility != 70) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
