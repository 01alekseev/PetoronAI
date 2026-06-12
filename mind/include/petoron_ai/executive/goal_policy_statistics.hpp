/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <string>
#include <vector>

namespace petoron_ai {

struct GoalPolicyStatistic {
    std::string goal_type;
    std::string policy_id;

    std::size_t success_count = 0;
    std::size_t failure_count = 0;
};

class GoalPolicyStatistics {
public:
    void add(
        const GoalPolicyStatistic& statistic
    );

    [[nodiscard]]
    std::size_t size() const;

    [[nodiscard]]
    const GoalPolicyStatistic& at(
        std::size_t index
    ) const;

private:
    std::vector<GoalPolicyStatistic> statistics_;
};

}
