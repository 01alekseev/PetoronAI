/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/policy/policy_evolution.hpp"

#include <cstdlib>

int main() {
    petoron_ai::EvolvingPolicy policy;

    const petoron_ai::ReinforcedStrategy shelter_up{
        "find shelter",
        95,
        105
    };

    const petoron_ai::ReinforcedStrategy shelter_up_again{
        "find shelter",
        105,
        115
    };

    const petoron_ai::ReinforcedStrategy storm_down{
        "walk into storm",
        -90,
        -110
    };

    const petoron_ai::ReinforcedStrategy unchanged{
        "keep distance",
        70,
        70
    };

    if (!petoron_ai::update_policy(policy, shelter_up)) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::update_policy(policy, shelter_up_again)) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::update_policy(policy, storm_down)) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::update_policy(policy, unchanged)) {
        return EXIT_FAILURE;
    }

    const auto* shelter =
        petoron_ai::find_policy_entry(
            policy,
            "find shelter"
        );

    if (shelter == nullptr) {
        return EXIT_FAILURE;
    }

    if (shelter->trust != 2) {
        return EXIT_FAILURE;
    }

    const auto* storm =
        petoron_ai::find_policy_entry(
            policy,
            "walk into storm"
        );

    if (storm == nullptr) {
        return EXIT_FAILURE;
    }

    if (storm->trust != -1) {
        return EXIT_FAILURE;
    }

    const auto* distance =
        petoron_ai::find_policy_entry(
            policy,
            "keep distance"
        );

    if (distance != nullptr) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
