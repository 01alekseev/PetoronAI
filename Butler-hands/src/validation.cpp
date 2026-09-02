/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/validation.hpp"

#include <stdexcept>
#include <unordered_set>

namespace butler_hands {
namespace {

void require_range(int value, const char* name) {
    if (value < 0 || value > 100) {
        throw std::invalid_argument(
            std::string(name) + " must be in range 0..100"
        );
    }
}

void require_non_negative(int value, const char* name) {
    if (value < 0) {
        throw std::invalid_argument(
            std::string(name) + " must be non-negative"
        );
    }
}

}

void validate_snapshot(const EnvironmentSnapshot& snapshot) {
    std::unordered_set<std::string> ids;

    for (const auto& observation : snapshot.observations) {
        if (observation.text.empty()) {
            throw std::invalid_argument("environment observation is empty");
        }
        require_range(observation.importance, "observation importance");
    }

    for (const auto& relation : snapshot.relations) {
        if (
            relation.subject.empty() ||
            relation.predicate.empty() ||
            relation.object.empty()
        ) {
            throw std::invalid_argument("environment relation contains an empty field");
        }
        require_range(relation.confidence, "relation confidence");
    }

    for (const auto& relation : snapshot.knowledge_relations) {
        if (relation.type.empty() || relation.from.empty() || relation.to.empty()) {
            throw std::invalid_argument("knowledge relation contains an empty field");
        }
    }

    if (snapshot.capabilities.empty()) {
        throw std::invalid_argument("environment exposes no capabilities");
    }

    for (const auto& capability : snapshot.capabilities) {
        if (capability.id.empty()) {
            throw std::invalid_argument("capability id is empty");
        }
        if (capability.description.empty()) {
            throw std::invalid_argument("capability description is empty");
        }
        if (!ids.insert(capability.id).second) {
            throw std::invalid_argument("duplicate capability id: " + capability.id);
        }

        require_range(capability.risk, "capability risk");
        require_range(capability.knowledge_value, "capability knowledge value");
        require_range(capability.safety_value, "capability safety value");
        require_non_negative(capability.resource_cost, "capability resource cost");
        require_non_negative(capability.time_cost, "capability time cost");
        require_non_negative(capability.energy_cost, "capability energy cost");
        require_non_negative(capability.memory_cost, "capability memory cost");
    }
}

void validate_config(const RuntimeConfig& config) {
    require_range(config.limits.maximum_risk, "maximum risk");
    require_non_negative(config.limits.time_budget, "time budget");
    require_non_negative(config.limits.energy_budget, "energy budget");
    require_non_negative(config.limits.memory_budget, "memory budget");

    if (config.limits.maximum_cycles == 0) {
        throw std::invalid_argument("maximum_cycles must be greater than zero");
    }
}

void validate_execution_result(const ExecutionResult& result) {
    if (result.outcome.empty()) {
        throw std::invalid_argument("execution outcome is empty");
    }
}

}
