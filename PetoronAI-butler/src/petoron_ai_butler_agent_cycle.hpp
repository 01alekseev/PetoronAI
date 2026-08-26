/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace petoron_ai_butler::internal {

struct AgentRule {
    std::string name;
    std::string left_payload;
    std::string right_payload;
    std::string conclusion_payload;
};

struct FutureBridgeResult {
    std::size_t outcome_count = 0;
    std::string selected_action;
    std::string selected_state;
    int selected_risk = 0;
};

struct PolicyBridgeResult {
    bool allows_selected = false;
    bool forbids_negative = false;
    std::size_t allowed_count = 0;
    std::size_t forbidden_count = 0;
    std::size_t filtered_count = 0;
    std::string selected_strategy;
    std::string forbidden_strategy;
    int selected_score = 0;
    bool policy_updated = false;
    std::string reinforced_strategy;
    int reinforced_old_score = 0;
    int reinforced_new_score = 0;
    int evolving_policy_trust = 0;
};

struct AgentCycleBridgeResult {
    std::size_t plan_steps = 0;
    std::size_t actions = 0;
    std::size_t feedback = 0;
    std::size_t trace_bytes = 0;
    bool trace_verified = false;
    bool trace_decoded = false;
    bool mind_state_committed = false;
    std::uint64_t cycle_count = 0;
};

class AgentCycleBridge {
public:
    AgentCycleBridge();
    ~AgentCycleBridge();

    AgentCycleBridge(const AgentCycleBridge&) = delete;
    AgentCycleBridge& operator=(const AgentCycleBridge&) = delete;

    AgentCycleBridge(AgentCycleBridge&&) noexcept;
    AgentCycleBridge& operator=(AgentCycleBridge&&) noexcept;

    void observe(
        const std::string& observation
    );

    AgentCycleBridgeResult run(
        const std::string& goal,
        const std::vector<AgentRule>& rules,
        std::uint64_t cycle_count
    );


    PolicyBridgeResult evaluate_policy(
        bool success,
        int reward
    );


    FutureBridgeResult simulate_future(
        const std::string& goal,
        const std::string& reason,
        int score
    );


    bool run_direct_api_probe();

    bool run_remaining_api_probe();

private:
    struct Impl;
    Impl* impl_;
};

}
