/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace butler_hands {

struct Observation {
    std::string text;
    int importance = 100;
};

struct Relation {
    std::string subject;
    std::string predicate;
    std::string object;
    int confidence = 100;
};

struct KnowledgeRelation {
    std::string type;
    std::string from;
    std::string to;
};

struct Capability {
    std::string id;
    std::string description;
    std::string action;
    int reward = 0;
    int risk = 0;
    int resource_cost = 0;
    int knowledge_value = 0;
    int safety_value = 0;
    int future_cost = 100;
    int time_cost = 0;
    int energy_cost = 0;
    int memory_cost = 0;
};

struct Constraint {
    std::string condition;
    std::string blocked_capability;
};

struct EnvironmentSnapshot {
    std::vector<Observation> observations;
    std::vector<Relation> relations;
    std::vector<std::string> knowledge;
    std::vector<KnowledgeRelation> knowledge_relations;
    std::vector<Capability> capabilities;
    std::vector<Constraint> constraints;
};

struct ExecutionRequest {
    std::string session_id;
    std::uint64_t cycle = 0;
    std::string goal;
    Capability capability;
};

struct ExecutionResult {
    bool success = false;
    std::string outcome;
    int reward = 0;
};

struct ResourceLimits {
    int maximum_risk = 100;
    std::size_t attention_limit = 10;
    int time_budget = 100;
    int energy_budget = 100;
    int memory_budget = 100;
    int baseline_future_cost = 100;
    std::uint64_t maximum_cycles = 1;
    std::chrono::milliseconds execution_timeout{0};
};

struct RuntimeConfig {
    ResourceLimits limits;
    bool stop_on_success = false;
    bool require_nonempty_observation = false;
};

struct CycleRecord {
    std::string session_id;
    std::uint64_t cycle = 0;
    std::string goal;
    std::string selected_capability;
    std::string butler_explanation;
    bool execution_success = false;
    std::string execution_outcome;
    int execution_reward = 0;
};

struct RunResult {
    bool success = false;
    std::string session_id;
    std::uint64_t cycles = 0;
    std::optional<CycleRecord> last_cycle;
};

}
