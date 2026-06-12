/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/risk_assessment.hpp"

#include <cstdlib>

int main() {
    const petoron_ai::RiskAssessment safe{
        90,
        10
    };

    if (
        petoron_ai::effective_score(
            safe
        ) != 80
    ) {
        return EXIT_FAILURE;
    }

    const petoron_ai::RiskAssessment dangerous{
        100,
        90
    };

    if (
        petoron_ai::effective_score(
            dangerous
        ) != 10
    ) {
        return EXIT_FAILURE;
    }

    if (
        petoron_ai::effective_score(
            safe
        ) <=
        petoron_ai::effective_score(
            dangerous
        )
    ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
