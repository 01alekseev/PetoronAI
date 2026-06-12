/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_analytics.hpp"

namespace petoron_ai {

ExecutiveAnalytics analyze_transitions(
    const ExecutiveTransitionLog& log
) {
    ExecutiveAnalytics result;

    for (const auto state : log.history()) {
        switch (state) {
            case ExecutiveState::Idle:
                ++result.idle_count;
                break;

            case ExecutiveState::Planning:
                ++result.planning_count;
                break;

            case ExecutiveState::Executing:
                ++result.executing_count;
                break;

            case ExecutiveState::Recovering:
                ++result.recovering_count;
                break;

            case ExecutiveState::Learning:
                ++result.learning_count;
                break;
        }
    }

    return result;
}

}
