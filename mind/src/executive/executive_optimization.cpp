/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_optimization.hpp"

namespace petoron_ai {

ExecutiveOptimization optimize_executive_cycle(
    const ExecutiveAnalytics& analytics
) {
    ExecutiveOptimization result;

    if (
        analytics.recovering_count >
        analytics.learning_count
    ) {
        result.reduce_recovery = true;
    }

    if (
        analytics.planning_count <
        analytics.executing_count
    ) {
        result.increase_planning = true;
    }

    return result;
}

}
