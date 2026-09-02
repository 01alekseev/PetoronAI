/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/validation.hpp"

#include <stdexcept>

int main() {
    butler_hands::EnvironmentSnapshot snapshot;

    snapshot.observations.push_back({
        "environment is observable",
        100
    });

    snapshot.capabilities.push_back({
        "observe_more",
        "Acquire additional evidence",
        "observe_more",
        10,
        0,
        1,
        100,
        100,
        1,
        1,
        1,
        1
    });

    butler_hands::validate_snapshot(snapshot);

    bool rejected_duplicate = false;

    snapshot.capabilities.push_back(
        snapshot.capabilities.front()
    );

    try {
        butler_hands::validate_snapshot(snapshot);
    } catch (const std::invalid_argument&) {
        rejected_duplicate = true;
    }

    if (!rejected_duplicate) {
        throw std::runtime_error(
            "duplicate capability was not rejected"
        );
    }

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 10;
    butler_hands::validate_config(config);

    return 0;
}
