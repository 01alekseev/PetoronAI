/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_reinforcement.hpp"

namespace petoron_ai {

void reinforce_policy(
    ExecutivePolicyRecord& record,
    const ExecutiveFeedback& feedback
) {
    if (feedback.positive) {
        ++record.success_count;
    }

    if (feedback.negative) {
        ++record.failure_count;
    }
}

}
