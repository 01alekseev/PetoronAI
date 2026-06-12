/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_decay.hpp"

#include <cstdlib>

int main() {
    using namespace petoron_ai;

    ExecutivePolicyRecord record;

    record.success_count = 10;
    record.failure_count = 4;

    decay_policy(record);

    if (record.success_count != 9) {
        return EXIT_FAILURE;
    }

    if (record.failure_count != 3) {
        return EXIT_FAILURE;
    }

    decay_policy(record);
    decay_policy(record);
    decay_policy(record);

    if (record.failure_count != 0) {
        return EXIT_FAILURE;
    }

    decay_policy(record);

    if (record.failure_count != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
