/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/executive_policy_selection.hpp"

#include <stdexcept>

namespace petoron_ai {

bool try_select_best_policy(
    const ExecutivePolicyHistory& history,
    std::size_t& selected_index
) {
    if (history.size() == 0) {
        return false;
    }

    double best_score = -1.0;

    for (std::size_t i = 0; i < history.size(); ++i) {
        const auto& record = history.at(i);

        const auto total =
            record.success_count +
            record.failure_count;

        const double score =
            total == 0
            ? 0.0
            : static_cast<double>(record.success_count) /
              static_cast<double>(total);

        if (score > best_score) {
            best_score = score;
            selected_index = i;
        }
    }

    return true;
}

const ExecutivePolicyRecord&
select_best_policy(
    const ExecutivePolicyHistory& history
) {
    std::size_t selected_index = 0;

    if (!try_select_best_policy(history, selected_index)) {
        throw std::out_of_range("empty executive policy history");
    }

    return history.at(selected_index);
}

}
