/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/runtime.hpp"
#include "butler_hands/file_audit_sink.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class TestEnvironment final : public butler_hands::Environment {
public:
    int observe_count = 0;
    int execute_count = 0;
    std::string executed_capability;

    butler_hands::EnvironmentSnapshot observe(
        const std::string& goal,
        std::uint64_t cycle
    ) override {
        ++observe_count;

        butler_hands::EnvironmentSnapshot snapshot;

        snapshot.observations.push_back({
            "cycle=" + std::to_string(cycle),
            100
        });

        snapshot.observations.push_back({
            "target requires safe evidence acquisition",
            100
        });

        snapshot.relations.push_back({
            goal,
            "requires",
            "evidence",
            100
        });

        snapshot.knowledge.push_back(
            "safe observation increases knowledge"
        );

        snapshot.knowledge_relations.push_back({
            "supports",
            "observation",
            "evidence"
        });

        snapshot.capabilities.push_back({
            "unsafe_action",
            "High-risk action",
            "unsafe_action",
            100,
            100,
            0,
            0,
            0,
            100,
            1,
            1,
            1
        });

        snapshot.capabilities.push_back({
            "observe_more",
            "Acquire additional evidence safely",
            "observe_more",
            50,
            0,
            0,
            100,
            100,
            0,
            1,
            1,
            1
        });

        return snapshot;
    }

    butler_hands::ExecutionResult execute(
        const butler_hands::ExecutionRequest& request
    ,
        const butler_hands::ExecutionContext&
    ) override {
        ++execute_count;
        executed_capability = request.capability.id;

        if (request.capability.id != "observe_more") {
            return {
                false,
                "unexpected capability executed",
                -100
            };
        }

        return {
            true,
            "evidence acquired",
            100
        };
    }
};

class TestPolicy final : public butler_hands::ExecutionPolicy {
public:
    int calls = 0;

    bool allow(
        const butler_hands::ExecutionRequest& request,
        std::string& reason
    ) const override {
        const_cast<TestPolicy*>(this)->calls++;

        if (request.capability.risk > 50) {
            reason = "risk rejected";
            return false;
        }

        reason.clear();
        return true;
    }
};

namespace {

void require_test(bool condition) {
    if (!condition) {
        throw std::runtime_error(
            "runtime_e2e_test requirement failed"
        );
    }
}

}

int main() {
    namespace fs = std::filesystem;

    const fs::path audit =
        fs::temp_directory_path() /
        "butler_hands_runtime_e2e.jsonl";

    fs::remove(audit);

    TestEnvironment environment;
    TestPolicy policy;
    butler_hands::FileAuditSink audit_sink(audit);

    butler_hands::Runtime runtime(
        environment,
        policy,
        audit_sink
    );

    butler_hands::RuntimeConfig config;

    config.limits.maximum_risk = 50;
    config.limits.attention_limit = 16;
    config.limits.time_budget = 100;
    config.limits.energy_budget = 100;
    config.limits.memory_budget = 100;
    config.limits.maximum_cycles = 1;

    config.stop_on_success = true;
    config.require_nonempty_observation = true;

    const auto result =
        runtime.run(
            "acquire reliable evidence",
            config
        );

    require_test(result.success);
    require_test(result.cycles == 1);
    require_test(result.last_cycle.has_value());

    require_test(environment.observe_count == 1);
    require_test(environment.execute_count == 1);

    require_test(
        environment.executed_capability ==
        "observe_more"
    );

    require_test(policy.calls == 1);

    require_test(
        result.last_cycle->selected_capability ==
        "observe_more"
    );

    require_test(
        result.last_cycle->execution_success
    );

    require_test(
        result.last_cycle->execution_outcome ==
        "evidence acquired"
    );

    require_test(fs::exists(audit));

    std::ifstream input(audit);

    std::string line;
    std::getline(input, line);

    require_test(!line.empty());

    require_test(
        line.find("\"selected_capability\":\"observe_more\"")
        != std::string::npos
    );

    require_test(
        line.find("\"execution_success\":true")
        != std::string::npos
    );

    fs::remove(audit);

    std::cout
        << "BUTLER_HANDS_E2E_PASS\n"
        << "selected=observe_more\n"
        << "observe_count="
        << environment.observe_count
        << "\nexecute_count="
        << environment.execute_count
        << "\npolicy_calls="
        << policy.calls
        << '\n';

    return 0;
}
