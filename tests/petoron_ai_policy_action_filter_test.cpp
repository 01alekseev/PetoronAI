/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/policy/policy_action_filter.hpp"

#include <cstdlib>

static bool has_strategy(
    const std::vector<petoron_ai::StrategyScore>& scores,
    const std::string& strategy
) {
    for (const auto& score : scores) {
        if (score.strategy == strategy) {
            return true;
        }
    }

    return false;
}

int main() {
    const auto policy =
        petoron_ai::build_policy({
            {"find shelter", 105},
            {"keep distance", 70},
            {"walk into storm", -110}
        });

    const auto filtered =
        petoron_ai::filter_strategies(
            policy,
            {
                {"find shelter", 105},
                {"keep distance", 70},
                {"walk into storm", -110},
                {"unknown", 15}
            }
        );

    if (filtered.size() != 3) {
        return EXIT_FAILURE;
    }

    if (!has_strategy(filtered, "find shelter")) {
        return EXIT_FAILURE;
    }

    if (!has_strategy(filtered, "keep distance")) {
        return EXIT_FAILURE;
    }

    if (!has_strategy(filtered, "unknown")) {
        return EXIT_FAILURE;
    }

    if (has_strategy(filtered, "walk into storm")) {
        return EXIT_FAILURE;
    }

    const auto best =
        petoron_ai::select_best_strategy(
            filtered
        );

    if (best.strategy != "find shelter") {
        return EXIT_FAILURE;
    }

    if (best.score != 105) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
