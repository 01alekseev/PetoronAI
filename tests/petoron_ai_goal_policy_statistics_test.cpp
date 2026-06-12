/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_statistics.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    GoalPolicyStatistics stats;

    GoalPolicyStatistic entry;

    entry.goal_type = "exploration";
    entry.policy_id = "policy_a";
    entry.success_count = 10;
    entry.failure_count = 2;

    stats.add(entry);

    if (stats.size() != 1) {
        return EXIT_FAILURE;
    }

    const auto& stored =
        stats.at(0);

    if (stored.goal_type != "exploration") {
        return EXIT_FAILURE;
    }

    if (stored.policy_id != "policy_a") {
        return EXIT_FAILURE;
    }

    if (stored.success_count != 10) {
        return EXIT_FAILURE;
    }

    if (stored.failure_count != 2) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
