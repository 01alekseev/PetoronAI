/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_decay.hpp"

namespace petoron_ai {

void decay_policy(
    ExecutivePolicyRecord& record
) {
    if (record.success_count > 0) {
        --record.success_count;
    }

    if (record.failure_count > 0) {
        --record.failure_count;
    }
}

}
