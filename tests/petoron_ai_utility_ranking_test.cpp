/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/utility_ranking.hpp"

#include <cstdlib>
#include <vector>

int main() {
    std::vector<petoron_ai::UtilityAssessment> strategies{
        {80, 40, 10, 5, 20},
        {90, 5, 0, 20, 0},
        {50, 10, 0, 0, 0}
    };

    const auto ranked =
        petoron_ai::rank_utilities(
            strategies
        );

    if (ranked.size() != 3) {
        return EXIT_FAILURE;
    }

    if (ranked[0].utility != 125) {
        return EXIT_FAILURE;
    }

    if (ranked[1].utility != 75) {
        return EXIT_FAILURE;
    }

    if (ranked[2].utility != 60) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
