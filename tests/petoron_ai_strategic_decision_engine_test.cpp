/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/strategic_decision_engine.hpp"

#include <cstdlib>

int main() {
    petoron_ai::StrategyPortfolio portfolio;

    portfolio.primary.utility = 150;

    const auto decision =
        petoron_ai::make_strategic_decision(
            portfolio
        );

    if (!decision.executable) {
        return EXIT_FAILURE;
    }

    if (decision.utility != 150) {
        return EXIT_FAILURE;
    }

    if (
        decision.decision
        !=
        "execute_primary_strategy"
    ) {
        return EXIT_FAILURE;
    }

    petoron_ai::StrategyPortfolio empty;

    const auto rejected =
        petoron_ai::make_strategic_decision(
            empty
        );

    if (rejected.executable) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
