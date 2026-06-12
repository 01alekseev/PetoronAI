/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/utility_engine.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    UtilityAssessment a;
    a.survival_value = 100;

    UtilityAssessment b;
    b.survival_value = 80;
    b.knowledge_value = 100;
    b.resource_value = 100;

    const auto ua = compute_utility(a);
    const auto ub = compute_utility(b);

    if (!(ub > ua)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
