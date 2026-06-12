/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_policy_history.hpp"
#include "petoron_ai/executive/executive_feedback.hpp"

namespace petoron_ai {

void reinforce_policy(
    ExecutivePolicyRecord& record,
    const ExecutiveFeedback& feedback
);

}
