/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/policy/policy_engine.hpp"

#include <cstdlib>

int main() {
    const auto policy =
        petoron_ai::build_policy({
            {"find shelter", 105},
            {"keep distance", 70},
            {"walk into storm", -110},
            {"unknown", 0}
        });

    if (policy.allowed.size() != 2) {
        return EXIT_FAILURE;
    }

    if (policy.forbidden.size() != 1) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::policy_allows(policy, "find shelter")) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::policy_allows(policy, "keep distance")) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::policy_forbids(policy, "walk into storm")) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::policy_allows(policy, "unknown")) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::policy_forbids(policy, "unknown")) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::policy_allows(policy, "walk into storm")) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::policy_forbids(policy, "find shelter")) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
