/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/runtime.hpp"
#include "butler_hands/file_audit_sink.hpp"

#include <atomic>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

namespace {

void require(bool value, const char* message) {
    if (!value) {
        throw std::runtime_error(message);
    }
}

class SlowEnvironment final : public butler_hands::Environment {
public:
    std::atomic<int> executes{0};
    std::atomic_bool executing{false};

    butler_hands::EnvironmentSnapshot observe(
        const std::string&,
        std::uint64_t cycle
    ) override {
        butler_hands::EnvironmentSnapshot snapshot;

        snapshot.observations.push_back({
            "cycle=" + std::to_string(cycle),
            100
        });

        snapshot.capabilities.push_back({
            "slow_action",
            "Slow safe action",
            "slow_action",
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
        ++executes;
        executing.store(true);

        while (!context.stop_requested()) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(1)
            );
        }

        executing.store(false);

        return {
            false,
            "execution stopped",
            1
        };
    }
};

class LongStressEnvironment final : public butler_hands::Environment {
public:
    int observes = 0;
    int executes = 0;

    butler_hands::EnvironmentSnapshot observe(
        const std::string&,
        std::uint64_t cycle
    ) override {
        ++observes;

        butler_hands::EnvironmentSnapshot snapshot;

        snapshot.observations.push_back({
            "long_stress_cycle=" + std::to_string(cycle),
            100
        });

        snapshot.capabilities.push_back({
            "continue",
            "Continue processing",
            "continue",
            1,
            0,
            0,
            1,
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
        ++executes;

        return {
            false,
            "step_" + std::to_string(executes),
            1
        };
    }
};

void test_concurrent_cancel() {
    SlowEnvironment environment;
    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;

    butler_hands::Runtime runtime(
        environment,
        policy,
        audit
    );

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 1000;
    config.stop_on_success = false;

    std::exception_ptr error;

    std::thread worker([&] {
        try {
            (void)runtime.run(
                "concurrent cancellation test",
                config
            );
        } catch (...) {
            error = std::current_exception();
        }
    });

    const auto wait_deadline =
        std::chrono::steady_clock::now() +
        std::chrono::seconds(2);

    while (
        !environment.executing.load() &&
        std::chrono::steady_clock::now() < wait_deadline
    ) {
        std::this_thread::yield();
    }

    require(
        environment.executing.load(),
        "environment execution did not start"
    );

    runtime.cancel();

    worker.join();

    bool cancellation_detected = false;

    if (error) {
        try {
            std::rethrow_exception(error);
        } catch (const std::runtime_error& e) {
            cancellation_detected =
                std::string(e.what()).find(
                    "environment execution cancelled"
                ) != std::string::npos;

            if (!cancellation_detected) {
                throw;
            }
        }
    }

    require(
        cancellation_detected,
        "runtime cancellation was not reported"
    );

    require(
        environment.executes.load() < 1000,
        "runtime ignored cancellation"
    );
}

void test_audit_write_failure() {
    namespace fs = std::filesystem;

    const fs::path bad_path =
        "/dev/null/impossible/audit.jsonl";

    bool rejected = false;

    try {
        butler_hands::FileAuditSink sink(bad_path);

        LongStressEnvironment environment;
        butler_hands::AllowAllExecutionPolicy policy;

        butler_hands::Runtime runtime(
            environment,
            policy,
            sink
        );

        butler_hands::RuntimeConfig config;
        config.limits.maximum_cycles = 1;

        (void)runtime.run(
            "audit failure test",
            config
        );
    } catch (const std::exception&) {
        rejected = true;
    }

    require(
        rejected,
        "invalid audit destination was silently accepted"
    );
}

void test_long_stress() {
    LongStressEnvironment environment;
    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;

    butler_hands::Runtime runtime(
        environment,
        policy,
        audit
    );

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 1000;
    config.stop_on_success = false;

    const auto result = runtime.run(
        "long stress test",
        config
    );

    require(
        result.cycles == 1000,
        "1000-cycle result mismatch"
    );

    require(
        environment.observes == 1000,
        "1000-cycle observation mismatch"
    );

    require(
        environment.executes == 1000,
        "1000-cycle execution mismatch"
    );
}

}

int main() {
    test_concurrent_cancel();
    test_audit_write_failure();
    test_long_stress();

    std::cout
        << "BUTLER_HANDS_DEEP_PASS\n"
        << "concurrent_cancel=PASS\n"
        << "audit_failure=PASS\n"
        << "stress_cycles=1000\n";

    return 0;
}
