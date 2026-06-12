/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_history.hpp"

namespace petoron_ai {

void ExecutivePolicyHistory::add(
    const ExecutivePolicyRecord& record
) {
    records_.push_back(record);
}

std::size_t ExecutivePolicyHistory::size() const {
    return records_.size();
}

const ExecutivePolicyRecord&
ExecutivePolicyHistory::at(
    std::size_t index
) const {
    return records_.at(index);
}

}
