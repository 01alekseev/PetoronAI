/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/planning/resource_budget.hpp"

namespace petoron_ai {

bool can_execute(
    const ResourceBudget& budget,
    const ResourceCost& cost
) {
    return
        cost.time_cost <= budget.time_budget &&
        cost.energy_cost <= budget.energy_budget &&
        cost.memory_cost <= budget.memory_budget;
}

}
