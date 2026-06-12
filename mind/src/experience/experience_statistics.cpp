/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/experience/experience_statistics.hpp"

#include <charconv>

namespace petoron_ai {

static int parse_int(
    const std::string& value
) {
    int out = 0;

    auto result =
        std::from_chars(
            value.data(),
            value.data() + value.size(),
            out
        );

    if (result.ec != std::errc{}) {
        return 0;
    }

    return out;
}

ExperienceStatistics experience_statistics(
    const KnowledgeStore& kb,
    const std::string& goal
) {
    ExperienceStatistics stats;

    const std::string experience_prefix =
        "experience_count:" + goal + ":";

    const std::string success_prefix =
        "success_count:" + goal + ":";

    const std::string failure_prefix =
        "failure_count:" + goal + ":";

    const std::string reward_prefix =
        "average_reward:" + goal + ":";

    for (const auto& fact : kb.facts()) {

        if (fact.rfind(experience_prefix, 0) == 0) {
            stats.experience_count =
                parse_int(
                    fact.substr(experience_prefix.size())
                );
        }

        if (fact.rfind(success_prefix, 0) == 0) {
            stats.success_count =
                parse_int(
                    fact.substr(success_prefix.size())
                );
        }

        if (fact.rfind(failure_prefix, 0) == 0) {
            stats.failure_count =
                parse_int(
                    fact.substr(failure_prefix.size())
                );
        }

        if (fact.rfind(reward_prefix, 0) == 0) {
            stats.average_reward =
                parse_int(
                    fact.substr(reward_prefix.size())
                );
        }
    }

    const int total =
        stats.success_count +
        stats.failure_count;

    if (total > 0) {
        stats.success_rate =
            (stats.success_count * 100) / total;
    }

    return stats;
}

}
