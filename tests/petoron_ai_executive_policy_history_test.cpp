/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_history.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutivePolicyHistory history;

    ExecutivePolicyRecord record;

    record.planning_depth = 3;
    record.strategy_diversity = 2;
    record.validation_level = 2;

    record.success_count = 7;
    record.failure_count = 1;

    history.add(record);

    if (history.size() != 1) {
        return EXIT_FAILURE;
    }

    const auto& stored =
        history.at(0);

    if (stored.planning_depth != 3) {
        return EXIT_FAILURE;
    }

    if (stored.strategy_diversity != 2) {
        return EXIT_FAILURE;
    }

    if (stored.validation_level != 2) {
        return EXIT_FAILURE;
    }

    if (stored.success_count != 7) {
        return EXIT_FAILURE;
    }

    if (stored.failure_count != 1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
