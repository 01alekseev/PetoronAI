/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_selection.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutivePolicyHistory history;

    ExecutivePolicyRecord weak;
    weak.planning_depth = 1;
    weak.success_count = 2;
    weak.failure_count = 8;

    ExecutivePolicyRecord strong;
    strong.planning_depth = 4;
    strong.success_count = 9;
    strong.failure_count = 1;

    history.add(weak);
    history.add(strong);

    const auto& best =
        select_best_policy(
            history
        );

    if (best.planning_depth != 4) {
        return EXIT_FAILURE;
    }

    if (best.success_count != 9) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
