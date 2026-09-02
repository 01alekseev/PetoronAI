/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/runtime.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

class MultiCycleEnvironment final : public butler_hands::Environment {
public:
    int observe_count = 0;
    int execute_count = 0;

    butler_hands::EnvironmentSnapshot observe(
        const std::string&,
        std::uint64_t cycle
    ) override {
        ++observe_count;

        butler_hands::EnvironmentSnapshot snapshot;

        snapshot.observations.push_back({
            "cycle=" + std::to_string(cycle),
            100
        });

        snapshot.knowledge.push_back(
            "repeated observation improves evidence"
        );

        snapshot.capabilities.push_back({
            "observe_more",
            "Acquire additional evidence",
            "observe_more",
            25,
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
        const butler_hands::ExecutionRequest&
    ,
        const butler_hands::ExecutionContext&
    ) override {
        ++execute_count;

        return {
            execute_count >= 3,
            "cycle_result_" + std::to_string(execute_count),
            50
        };
    }
};

int main() {
    MultiCycleEnvironment environment;
    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;

    butler_hands::Runtime runtime(
        environment,
        policy,
        audit
    );

    butler_hands::RuntimeConfig config;

    config.limits.maximum_cycles = 3;
    config.limits.maximum_risk = 100;
    config.stop_on_success = true;
    config.require_nonempty_observation = true;

    const auto result =
        runtime.run(
            "collect sufficient evidence",
            config
        );

    if (!result.success) {
        throw std::runtime_error(
            "multi-cycle runtime did not finish successfully"
        );
    }

    if (result.cycles != 3) {
        throw std::runtime_error(
            "unexpected cycle count"
        );
    }

    if (
        environment.observe_count != 3 ||
        environment.execute_count != 3
    ) {
        throw std::runtime_error(
            "environment cycle count mismatch"
        );
    }

    if (!result.last_cycle.has_value()) {
        throw std::runtime_error(
            "last cycle missing"
        );
    }

    if (
        result.last_cycle->execution_outcome !=
        "cycle_result_3"
    ) {
        throw std::runtime_error(
            "wrong final outcome"
        );
    }

    std::cout
        << "BUTLER_HANDS_MULTICYCLE_PASS\n"
        << "cycles=" << result.cycles << '\n'
        << "observe_count=" << environment.observe_count << '\n'
        << "execute_count=" << environment.execute_count << '\n';

    return 0;
}
