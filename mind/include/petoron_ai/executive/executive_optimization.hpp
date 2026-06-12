/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_analytics.hpp"

namespace petoron_ai {

struct ExecutiveOptimization {
    bool increase_planning = false;
    bool reduce_recovery = false;
};

ExecutiveOptimization optimize_executive_cycle(
    const ExecutiveAnalytics& analytics
);

}
