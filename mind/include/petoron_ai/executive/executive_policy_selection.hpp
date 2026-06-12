/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/executive/executive_policy_history.hpp"

#include <cstddef>

namespace petoron_ai {

bool try_select_best_policy(
    const ExecutivePolicyHistory& history,
    std::size_t& selected_index
);

const ExecutivePolicyRecord&
select_best_policy(
    const ExecutivePolicyHistory& history
);

}
