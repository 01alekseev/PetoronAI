/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/runtime.hpp"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

class TimeoutEnvironment final : public butler_hands::Environment {
public:
    butler_hands::EnvironmentSnapshot observe(
        const std::string&,
        std::uint64_t
    ) override {
        butler_hands::EnvironmentSnapshot snapshot;

        snapshot.observations.push_back({
            "timeout test observation",
            100
        });

        snapshot.capabilities.push_back({
            "slow_operation",
            "Cancellable slow operation",
            "slow_operation",
            10,
            0,
            0,
            10,
            100,
            0,
            1,
            1,
            1
        });

        return snapshot;
    }

    butler_hands::ExecutionResult execute(
        const butler_hands::ExecutionRequest&,
        const butler_hands::ExecutionContext& context
    ) override {
        for (int i = 0; i < 500; ++i) {
            if (context.stop_requested()) {
                return {
                    false,
                    "execution stopped by deadline",
                    -100
                };
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(1)
            );
        }

        return {
            true,
            "slow operation completed",
            10
        };
    }
};

int main() {
    TimeoutEnvironment environment;
    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;

    butler_hands::Runtime runtime(
        environment,
        policy,
        audit
    );

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 1;
    config.limits.execution_timeout =
        std::chrono::milliseconds(50);

    const auto begin =
        std::chrono::steady_clock::now();

    bool timeout_detected = false;

    try {
        (void)runtime.run("timeout test", config);
    } catch (const std::runtime_error& e) {
        timeout_detected =
            std::string(e.what()).find("timed out") !=
            std::string::npos;

        std::cout << "exception=" << e.what() << '\n';
    }

    const auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - begin
        ).count();

    std::cout << "elapsed_ms=" << elapsed << '\n';

    if (!timeout_detected) {
        throw std::runtime_error(
            "execution timeout was not detected"
        );
    }

    if (elapsed > 150) {
        throw std::runtime_error(
            "cooperative timeout exceeded latency bound"
        );
    }

    std::cout << "BUTLER_HANDS_TIMEOUT_PASS\n";
    return 0;
}
