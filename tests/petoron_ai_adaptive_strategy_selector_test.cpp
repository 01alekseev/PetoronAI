/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/adaptive_strategy_selector.hpp"

#include <cstdlib>
#include <vector>

int main() {
    const std::vector<petoron_ai::AdaptiveStrategy> strategies{
        {"Strategy A", 95, 100},
        {"Strategy B", 90, 20},
        {"Strategy C", 50, 10}
    };

    const auto selected =
        petoron_ai::select_strategy(
            strategies,
            30
        );

    if (selected.name != "Strategy B") {
        return EXIT_FAILURE;
    }

    if (selected.score != 90) {
        return EXIT_FAILURE;
    }

    const auto none =
        petoron_ai::select_strategy(
            strategies,
            5
        );

    if (!none.name.empty()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
