/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/resource_budget.hpp"

#include <cstdlib>

int main() {
    const petoron_ai::ResourceBudget budget{
        100,
        50,
        20
    };

    const petoron_ai::ResourceCost affordable{
        40,
        10,
        5
    };

    if (!petoron_ai::can_execute(budget, affordable)) {
        return EXIT_FAILURE;
    }

    const petoron_ai::ResourceCost too_expensive{
        120,
        10,
        5
    };

    if (petoron_ai::can_execute(budget, too_expensive)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
