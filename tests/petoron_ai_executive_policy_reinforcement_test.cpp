/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_reinforcement.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutivePolicyRecord record;

    record.success_count = 5;
    record.failure_count = 2;

    ExecutiveFeedback positive;
    positive.positive = true;

    reinforce_policy(
        record,
        positive
    );

    if (record.success_count != 6) {
        return EXIT_FAILURE;
    }

    ExecutiveFeedback negative;
    negative.negative = true;

    reinforce_policy(
        record,
        negative
    );

    if (record.failure_count != 3) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
