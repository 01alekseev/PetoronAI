/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_transition_log.hpp"

namespace petoron_ai {

struct ExecutiveAnalytics {
    std::size_t idle_count = 0;
    std::size_t planning_count = 0;
    std::size_t executing_count = 0;
    std::size_t recovering_count = 0;
    std::size_t learning_count = 0;
};

ExecutiveAnalytics analyze_transitions(
    const ExecutiveTransitionLog& log
);

}
