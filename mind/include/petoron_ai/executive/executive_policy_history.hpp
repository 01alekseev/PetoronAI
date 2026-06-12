/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <cstddef>
#include <vector>

namespace petoron_ai {

struct ExecutivePolicyRecord {
    int planning_depth = 1;
    int strategy_diversity = 1;
    int validation_level = 1;

    std::size_t success_count = 0;
    std::size_t failure_count = 0;
};

class ExecutivePolicyHistory {
public:
    void add(
        const ExecutivePolicyRecord& record
    );

    [[nodiscard]]
    std::size_t size() const;

    [[nodiscard]]
    const ExecutivePolicyRecord& at(
        std::size_t index
    ) const;

private:
    std::vector<ExecutivePolicyRecord> records_;
};

}
