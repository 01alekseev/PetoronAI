/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_feedback.hpp"
#include "petoron_ai/executive/executive_analytics.hpp"

namespace petoron_ai {

ExecutiveAnalytics integrate_executive_feedback(
    const ExecutiveAnalytics& analytics,
    const ExecutiveFeedback& feedback
);

}
