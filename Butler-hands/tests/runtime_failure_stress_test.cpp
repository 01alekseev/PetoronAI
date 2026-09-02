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

namespace {

void require(bool value, const char* message) {
    if (!value) {
        throw std::runtime_error(message);
    }
}

class RejectPolicy final : public butler_hands::ExecutionPolicy {
public:
    bool allow(
        const butler_hands::ExecutionRequest&,
        std::string& reason
    ) const override {
        reason = "policy rejected capability";
        return false;
    }
};

class SingleEnvironment final : public butler_hands::Environment {
public:
    enum class Mode {
        Normal,
        ThrowExecute,
        EmptyOutcome
    };

    explicit SingleEnvironment(Mode mode = Mode::Normal)
        : mode_(mode) {}

    int execute_count = 0;

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
            "safe_capability",
            "Safe executable capability",
            "safe_capability",
            50,
            0,
            0,
            50,
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

        if (mode_ == Mode::ThrowExecute) {
            throw std::runtime_error("environment execution failure");
        }

        if (mode_ == Mode::EmptyOutcome) {
            return {true, "", 10};
        }

        return {true, "executed", 10};
    }

private:
    Mode mode_;
};

class StressEnvironment final : public butler_hands::Environment {
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
            "stress_cycle=" + std::to_string(cycle),
            100
        });

        snapshot.knowledge.push_back(
            "continue until cycle budget is exhausted"
        );

        snapshot.capabilities.push_back({
            "continue",
            "Continue safe reasoning cycle",
            "continue",
            10,
            0,
            0,
            20,
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
            false,
            "stress_step_" + std::to_string(execute_count),
            1
        };
    }
};

void test_policy_reject() {
    SingleEnvironment environment;
    RejectPolicy policy;
    butler_hands::NullAuditSink audit;
    butler_hands::Runtime runtime(environment, policy, audit);

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 1;

    bool rejected = false;

    try {
        (void)runtime.run("policy test", config);
    } catch (const std::runtime_error& e) {
        rejected =
            std::string(e.what()).find("policy rejected") !=
            std::string::npos;
    }

    require(rejected, "policy rejection was not enforced");
    require(environment.execute_count == 0,
            "rejected capability was executed");
}

void test_environment_exception() {
    SingleEnvironment environment(
        SingleEnvironment::Mode::ThrowExecute
    );

    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;
    butler_hands::Runtime runtime(environment, policy, audit);

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 1;

    bool caught = false;

    try {
        (void)runtime.run("exception test", config);
    } catch (const std::runtime_error& e) {
        caught =
            std::string(e.what()).find(
                "environment execution failure"
            ) != std::string::npos;
    }

    require(caught, "environment exception was not propagated");
}

void test_empty_outcome_rejected() {
    SingleEnvironment environment(
        SingleEnvironment::Mode::EmptyOutcome
    );

    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;
    butler_hands::Runtime runtime(environment, policy, audit);

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 1;

    bool rejected = false;

    try {
        (void)runtime.run("empty outcome test", config);
    } catch (const std::invalid_argument&) {
        rejected = true;
    }

    require(rejected, "empty execution outcome was accepted");
}

void test_invalid_risk_config() {
    SingleEnvironment environment;
    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;
    butler_hands::Runtime runtime(environment, policy, audit);

    butler_hands::RuntimeConfig config;
    config.limits.maximum_risk = 101;

    bool rejected = false;

    try {
        (void)runtime.run("invalid risk", config);
    } catch (const std::invalid_argument&) {
        rejected = true;
    }

    require(rejected, "invalid maximum_risk was accepted");
}

void test_file_audit() {
    namespace fs = std::filesystem;

    const auto path =
        fs::temp_directory_path() /
        "butler_hands_failure_stress.jsonl";

    fs::remove(path);

    SingleEnvironment environment;
    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::FileAuditSink audit(path);
    butler_hands::Runtime runtime(environment, policy, audit);

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 1;
    config.stop_on_success = true;

    const auto result = runtime.run("audit test", config);

    require(result.success, "audit test execution failed");
    require(fs::exists(path), "audit file was not created");

    std::ifstream in(path);
    std::string line;
    std::getline(in, line);

    require(!line.empty(), "audit record is empty");
    require(
        line.find("\"selected_capability\":\"safe_capability\"")
            != std::string::npos,
        "audit selected capability missing"
    );

    fs::remove(path);
}

void test_stress_100_cycles() {
    StressEnvironment environment;
    butler_hands::AllowAllExecutionPolicy policy;
    butler_hands::NullAuditSink audit;
    butler_hands::Runtime runtime(environment, policy, audit);

    butler_hands::RuntimeConfig config;
    config.limits.maximum_cycles = 100;
    config.limits.maximum_risk = 100;
    config.stop_on_success = false;

    const auto result =
        runtime.run("stress runtime", config);

    require(result.cycles == 100, "stress cycle count mismatch");
    require(environment.observe_count == 100,
            "stress observe count mismatch");
    require(environment.execute_count == 100,
            "stress execute count mismatch");
}

}

int main() {
    test_policy_reject();
    test_environment_exception();
    test_empty_outcome_rejected();
    test_invalid_risk_config();
    test_file_audit();
    test_stress_100_cycles();

    std::cout << "BUTLER_HANDS_FAILURE_STRESS_PASS\n";
    std::cout << "policy_reject=PASS\n";
    std::cout << "environment_exception=PASS\n";
    std::cout << "empty_outcome=PASS\n";
    std::cout << "invalid_config=PASS\n";
    std::cout << "audit=PASS\n";
    std::cout << "stress_cycles=100\n";

    return 0;
}
