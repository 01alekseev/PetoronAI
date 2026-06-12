/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

namespace petoron_ai {

struct ResourceBudget {
    int time_budget = 0;
    int energy_budget = 0;
    int memory_budget = 0;
};

struct ResourceCost {
    int time_cost = 0;
    int energy_cost = 0;
    int memory_cost = 0;
};

bool can_execute(
    const ResourceBudget& budget,
    const ResourceCost& cost
);

}
