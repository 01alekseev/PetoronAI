/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_transition_log.hpp"

namespace petoron_ai {

void ExecutiveTransitionLog::record(
    ExecutiveState state
) {
    history_.push_back(state);
}

const std::vector<ExecutiveState>&
ExecutiveTransitionLog::history() const {
    return history_;
}

std::size_t
ExecutiveTransitionLog::size() const {
    return history_.size();
}

}
