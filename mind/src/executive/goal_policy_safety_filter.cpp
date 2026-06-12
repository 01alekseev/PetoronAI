/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/executive/goal_policy_safety_filter.hpp"

namespace petoron_ai {

bool is_policy_safe(
    const ExecutiveSafetyState& state,
    const std::string& policy_id
) {
    if (
        policy_id == "collect_resources" &&
        state.risk >= 70
    ) {
        return false;
    }

    if (
        policy_id == "collect_resources" &&
        state.resources >= 85
    ) {
        return false;
    }

    if (
        policy_id == "collect_resources" &&
        state.safety <= 30
    ) {
        return false;
    }

    if (
        policy_id == "secure_shelter" &&
        state.safety >= 90 &&
        state.risk < 40
    ) {
        return false;
    }

    if (
        policy_id == "collect_resources" &&
        state.survival <= 50 &&
        state.risk >= 40
    ) {
        return false;
    }

    if (
        policy_id == "observe_environment" &&
        state.resources <= 15
    ) {
        return false;
    }

    if (
        policy_id == "observe_environment" &&
        state.knowledge >= 100 &&
        state.risk <= 10
    ) {
        return false;
    }

    if (
        policy_id == "maintain_stability" &&
        (
            state.risk >= 40 ||
            state.survival <= 70 ||
            state.resources <= 20 ||
            state.safety <= 70
        )
    ) {
        return false;
    }

    if (
        policy_id == "reduce_risk" &&
        state.risk <= 15
    ) {
        return false;
    }

    return true;
}

}
