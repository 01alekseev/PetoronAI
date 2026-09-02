/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "butler_hands/runtime.hpp"
#include "butler_hands/validation.hpp"

#include <chrono>
#include <random>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace butler_hands {
namespace {

std::string make_session_id() {
    const auto now = std::chrono::high_resolution_clock::now()
        .time_since_epoch().count();

    std::random_device rd;
    std::mt19937_64 engine(
        static_cast<std::mt19937_64::result_type>(now) ^
        static_cast<std::mt19937_64::result_type>(rd())
    );

    std::ostringstream out;
    out << std::hex << now << '-' << engine();
    return out.str();
}

petoron_ai_butler::Candidate to_candidate(const Capability& capability) {
    return {
        capability.id,
        capability.description,
        capability.action.empty() ? capability.id : capability.action,
        capability.reward,
        capability.risk,
        capability.resource_cost,
        capability.knowledge_value,
        capability.safety_value,
        capability.future_cost,
        capability.time_cost,
        capability.energy_cost,
        capability.memory_cost
    };
}

petoron_ai_butler::Request to_request(
    const std::string& goal,
    const EnvironmentSnapshot& snapshot,
    const RuntimeConfig& config
) {
    petoron_ai_butler::Request request;
    request.goal = goal;
    request.maximum_risk = config.limits.maximum_risk;
    request.baseline_future_cost = config.limits.baseline_future_cost;
    request.attention_limit = config.limits.attention_limit;
    request.time_budget = config.limits.time_budget;
    request.energy_budget = config.limits.energy_budget;
    request.memory_budget = config.limits.memory_budget;

    request.constraints.reserve(snapshot.constraints.size());
    for (const auto& constraint : snapshot.constraints) {
        request.constraints.push_back({
            constraint.condition,
            constraint.blocked_capability
        });
    }

    return request;
}

ExecutionResult execute_with_control(
    Environment& environment,
    const ExecutionRequest& request,
    const ExecutionContext& context
) {
    if (context.stop_requested()) {
        if (context.deadline_exceeded()) {
            throw std::runtime_error(
                "environment execution timed out"
            );
        }

        throw std::runtime_error(
            "environment execution cancelled"
        );
    }

    const auto result =
        environment.execute(request, context);

    if (context.deadline_exceeded()) {
        throw std::runtime_error(
            "environment execution timed out"
        );
    }

    if (context.cancellation_requested()) {
        throw std::runtime_error(
            "environment execution cancelled"
        );
    }

    return result;
}

}

Runtime::Runtime(
    Environment& environment,
    ExecutionPolicy& policy,
    AuditSink& audit
)
    : environment_(environment),
      policy_(policy),
      audit_(audit) {
}

RunResult Runtime::run(
    const std::string& goal,
    const RuntimeConfig& config
) {
    if (goal.empty()) {
        throw std::invalid_argument("goal is empty");
    }

    validate_config(config);
    cancelled_.store(false);

    const std::string session_id = make_session_id();
    RunResult run_result;
    run_result.session_id = session_id;

    std::vector<petoron_ai_butler::Feedback> feedback_history;
    std::vector<petoron_ai_butler::Experience> experience_history;

    for (std::uint64_t cycle = 1;
         cycle <= config.limits.maximum_cycles;
         ++cycle) {
        if (cancelled_.load()) {
            break;
        }

        const auto snapshot = environment_.observe(goal, cycle);
        validate_snapshot(snapshot);

        if (
            config.require_nonempty_observation &&
            snapshot.observations.empty()
        ) {
            throw std::runtime_error("environment returned no observations");
        }

        butler_.reset();
        butler_.set_goal(goal);

        for (const auto& feedback : feedback_history) {
            butler_.apply_feedback(feedback);
        }

        for (const auto& experience : experience_history) {
            butler_.add_experience(experience);
        }

        for (const auto& observation : snapshot.observations) {
            butler_.add_fact(observation.text, observation.importance);
            butler_.add_mind_observation(observation.text);
        }

        for (const auto& relation : snapshot.relations) {
            butler_.add_relation(
                relation.subject,
                relation.predicate,
                relation.object,
                relation.confidence
            );
        }

        for (const auto& fact : snapshot.knowledge) {
            if (fact.empty()) {
                throw std::invalid_argument("environment knowledge fact is empty");
            }
            butler_.add_knowledge(fact);
        }

        for (const auto& relation : snapshot.knowledge_relations) {
            butler_.add_knowledge_relation(
                relation.type,
                relation.from,
                relation.to
            );
        }

        std::unordered_map<std::string, Capability> capabilities;
        capabilities.reserve(snapshot.capabilities.size());

        for (const auto& capability : snapshot.capabilities) {
            butler_.add_candidate(to_candidate(capability));
            capabilities.emplace(capability.id, capability);
        }

        const auto decision = butler_.run(
            to_request(goal, snapshot, config)
        );

        const auto selected = capabilities.find(
            decision.selected_candidate
        );

        if (selected == capabilities.end()) {
            throw std::runtime_error(
                "Butler selected an unknown capability: " +
                decision.selected_candidate
            );
        }

        ExecutionRequest execution_request{
            session_id,
            cycle,
            goal,
            selected->second
        };

        std::string rejection_reason;
        if (!policy_.allow(execution_request, rejection_reason)) {
            if (rejection_reason.empty()) {
                rejection_reason = "execution policy rejected capability";
            }

            const petoron_ai_butler::Feedback feedback{
                decision.selected_candidate,
                -100
            };

            const petoron_ai_butler::Experience experience{
                goal,
                selected->second.action.empty()
                    ? selected->second.id
                    : selected->second.action,
                selected->second.risk,
                rejection_reason,
                -100
            };

            butler_.apply_feedback(feedback);
            butler_.add_experience(experience);

            feedback_history.push_back(feedback);
            experience_history.push_back(experience);

            throw std::runtime_error(rejection_reason);
        }

        const ExecutionContext execution_context(
            cancelled_,
            config.limits.execution_timeout
        );

        const auto execution = execute_with_control(
            environment_,
            execution_request,
            execution_context
        );

        validate_execution_result(execution);

        const petoron_ai_butler::Feedback feedback{
            decision.selected_candidate,
            execution.reward
        };

        const petoron_ai_butler::Experience experience{
            goal,
            selected->second.action.empty()
                ? selected->second.id
                : selected->second.action,
            selected->second.risk,
            execution.outcome,
            execution.reward
        };

        butler_.apply_feedback(feedback);
        butler_.add_experience(experience);

        feedback_history.push_back(feedback);
        experience_history.push_back(experience);

        CycleRecord record;
        record.session_id = session_id;
        record.cycle = cycle;
        record.goal = goal;
        record.selected_capability = decision.selected_candidate;
        record.butler_explanation = decision.explanation;
        record.execution_success = execution.success;
        record.execution_outcome = execution.outcome;
        record.execution_reward = execution.reward;

        audit_.record(record);

        run_result.cycles = cycle;
        run_result.last_cycle = record;
        run_result.success = execution.success;

        if (execution.success && config.stop_on_success) {
            break;
        }
    }

    return run_result;
}

void Runtime::cancel() noexcept {
    cancelled_.store(true);
}

}
