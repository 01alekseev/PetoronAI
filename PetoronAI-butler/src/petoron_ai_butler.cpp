/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai_butler.hpp"
#include "petoron_ai_butler_agent_cycle.hpp"

#include "petoron_ai/concept/concept_artifact.hpp"
#include "petoron_ai/concept/concept_store.hpp"
#include "petoron_ai/decision/decision_arena.hpp"
#include "petoron_ai/meta/meta_reasoning_artifact.hpp"
#include "petoron_ai/reflection/reflection_artifact.hpp"
#include "petoron_ai/experience/self_improvement.hpp"
#include "petoron_ai/experience/experience_engine.hpp"
#include "petoron_ai/experience/experience_file.hpp"
#include "petoron_ai/experience/experience_statistics.hpp"
#include "petoron_ai/executive/goal_aware_policy_selection.hpp"
#include "petoron_ai/executive/goal_policy_confidence.hpp"
#include "petoron_ai/executive/goal_policy_evidence.hpp"
#include "petoron_ai/executive/goal_policy_statistics.hpp"
#include "petoron_ai/executive/goal_policy_decay.hpp"
#include "petoron_ai/executive/goal_policy_reinforcement.hpp"
#include "petoron_ai/executive/goal_policy_safe_ucb_selection.hpp"
#include "petoron_ai/executive/goal_policy_safety_filter.hpp"
#include "petoron_ai/executive/goal_policy_ucb_selection.hpp"
#include "petoron_ai/executive/executive_policy_decay.hpp"
#include "petoron_ai/executive/executive_policy_history.hpp"
#include "petoron_ai/executive/executive_policy_reinforcement.hpp"
#include "petoron_ai/executive/executive_policy_selection.hpp"
#include "petoron_ai/goal/goal_adaptation.hpp"
#include "petoron_ai/goal/goal_priority_selector.hpp"
#include "petoron_ai/goal/goal_scheduler.hpp"
#include "petoron_ai/goal/goal_stack.hpp"
#include "petoron_ai/executive/executive_controller.hpp"
#include "petoron_ai/executive/executive_orchestrator.hpp"
#include "petoron_ai/executive/executive_cycle.hpp"
#include "petoron_ai/executive/executive_feedback.hpp"
#include "petoron_ai/executive/executive_feedback_integration.hpp"
#include "petoron_ai/executive/executive_analytics.hpp"
#include "petoron_ai/knowledge/knowledge_feedback_delta.hpp"
#include "petoron_ai/knowledge/knowledge_relation.hpp"
#include "petoron_ai/knowledge/knowledge_store.hpp"
#include "petoron_ai/memory/attention_engine.hpp"
#include "petoron_ai/memory/context_builder.hpp"
#include "petoron_ai/memory/long_term_memory.hpp"
#include "petoron_ai/planning/constraint_engine.hpp"
#include "petoron_ai/planning/decision_explanation.hpp"
#include "petoron_ai/planning/decision_selector.hpp"
#include "petoron_ai/planning/goal_tree.hpp"
#include "petoron_ai/planning/planner.hpp"
#include "petoron_ai/planning/resource_budget.hpp"
#include "petoron_ai/reasoning/counterfactual_reasoning.hpp"
#include "petoron_ai/reasoning/hypothesis_evaluation.hpp"
#include "petoron_ai/reasoning/hypothesis_generator.hpp"
#include "petoron_ai/petoron_mind.hpp"
#include "petoron_ai/reasoning_proof_input.hpp"
#include "petoron_ai/reasoning_proof_input_codec.hpp"
#include "petoron_ai/reasoning_proof_package.hpp"
#include "petoron_ai/reasoning_trace.hpp"
#include "petoron_ai/reasoning_trace_codec.hpp"
#include "petoron_ai/runtime/action_execution.hpp"
#include "petoron_ai/runtime/execution_monitor.hpp"
#include "petoron_ai/runtime/execution_recovery.hpp"
#include "petoron_ai/runtime/outcome_evaluation.hpp"
#include "petoron_ai/strategy/adaptive_strategy_selector.hpp"
#include "petoron_ai/strategy/risk_assessment.hpp"
#include "petoron_ai/strategy/utility_engine.hpp"
#include "petoron_ai/strategy/reward_assessment.hpp"
#include "petoron_ai/strategy/strategic_decision_engine.hpp"
#include "petoron_ai/strategy/strategy_artifact.hpp"
#include "petoron_ai/strategy/strategy_evolution.hpp"
#include "petoron_ai/strategy/strategy_planner.hpp"
#include "petoron_ai/strategy/strategy_portfolio.hpp"
#include "petoron_ai/strategy/strategy_store.hpp"
#include "petoron_ai/strategy/strategy_experience.hpp"
#include "petoron_ai/strategy/strategy_switching.hpp"
#include "petoron_ai/strategy/utility_ranking.hpp"
#include "petoron_ai/thought/thought_artifact.hpp"
#include "petoron_ai/thought/thought_chain.hpp"
#include "petoron_ai/thought/thought_graph.hpp"
#include "petoron_ai/thought/thought_search.hpp"
#include "petoron_ai/thought/thought_store.hpp"
#include "petoron_ai/world/world_model.hpp"
#include "petoron_ai/world/world_reasoning.hpp"
#include "petoron_ai/world/world_simulation.hpp"
#include "petoron_ai/world/world_state_transition.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace petoron_ai_butler {

struct Butler::Impl {
    std::string goal;
    std::vector<Fact> facts;
    std::vector<Relation> relations;
    std::vector<Candidate> candidates;
    std::vector<KnowledgeRelation> knowledge_relations;
    std::vector<ThoughtConnection> thought_connections;
    petoron_ai::KnowledgeStore knowledge;
    petoron_ai::ConceptStore concepts;
    petoron_ai::ThoughtStore thoughts;
    internal::AgentCycleBridge agent_cycle;
    petoron_ai::PetoronMind reasoning_mind;
    std::vector<std::string> mind_observations;
    std::vector<MindReasoningRule> mind_reasoning_rules;
    std::uint64_t mind_cycle_count = 0;
    petoron_ai::ExecutiveController executive;
    petoron_ai::GoalAdaptationState goal_adaptation;
    std::vector<GoalPolicyRecord> goal_policy_records;
    petoron_ai::ExecutiveAnalytics executive_analytics{};
    petoron_ai::ExecutiveFeedback executive_feedback{};
    petoron_ai::StrategyStore strategy_store;
    petoron_ai::SelfImprovementState learning;
};

namespace {

void validate_range(
    int value,
    const std::string& name
) {
    if (value < 0 || value > 100) {
        throw std::invalid_argument(
            name + " must be in range 0..100"
        );
    }
}

void validate_non_negative(
    int value,
    const std::string& name
) {
    if (value < 0) {
        throw std::invalid_argument(
            name + " must be non-negative"
        );
    }
}

void validate_candidate(
    const Candidate& candidate
) {
    if (candidate.id.empty()) {
        throw std::invalid_argument(
            "candidate id is empty"
        );
    }

    if (candidate.description.empty()) {
        throw std::invalid_argument(
            "candidate description is empty"
        );
    }

    validate_range(
        candidate.risk,
        "candidate risk"
    );

    validate_range(
        candidate.knowledge_value,
        "candidate knowledge value"
    );

    validate_range(
        candidate.safety_value,
        "candidate safety value"
    );

    validate_non_negative(
        candidate.resource_cost,
        "candidate resource cost"
    );

    validate_non_negative(
        candidate.time_cost,
        "candidate time cost"
    );

    validate_non_negative(
        candidate.energy_cost,
        "candidate energy cost"
    );

    validate_non_negative(
        candidate.memory_cost,
        "candidate memory cost"
    );
}

std::vector<std::string> make_world_facts(
    const std::string& goal,
    const std::vector<Fact>& facts,
    const std::vector<Relation>& relations,
    const std::vector<Candidate>& candidates,
    const petoron_ai::KnowledgeStore& knowledge
) {
    std::vector<std::string> world_facts =
        knowledge.facts();

    world_facts.reserve(
        world_facts.size() +
        1 +
        facts.size() +
        relations.size() +
        candidates.size()
    );

    world_facts.push_back(
        "goal=" + goal
    );

    for (const Fact& fact : facts) {
        world_facts.push_back(
            fact.text
        );
    }

    for (const Relation& relation : relations) {
        world_facts.push_back(
            relation.subject +
            " " +
            relation.predicate +
            " " +
            relation.object
        );
    }

    for (const Candidate& candidate : candidates) {
        world_facts.push_back(
            "candidate=" +
            candidate.id +
            " description=" +
            candidate.description
        );
    }

    return world_facts;
}

std::vector<petoron_ai::ThoughtEdge> make_thought_edges(
    const petoron_ai::ThoughtStore& store,
    const std::vector<ThoughtConnection>& connections
) {
    std::vector<petoron_ai::ThoughtEdge> edges;

    edges.reserve(
        connections.size()
    );

    for (const ThoughtConnection& connection : connections) {
        if (
            connection.from >= store.thoughts.size() ||
            connection.to >= store.thoughts.size()
        ) {
            throw std::out_of_range(
                "thought connection index is out of range"
            );
        }

        edges.push_back({
            store.thoughts[connection.from].id,
            store.thoughts[connection.to].id,
            connection.weight
        });
    }

    return edges;
}

const char* execution_status_name(
    petoron_ai::ExecutionStatus status
) {
    switch (status) {
        case petoron_ai::ExecutionStatus::Pending:
            return "pending";
        case petoron_ai::ExecutionStatus::Running:
            return "running";
        case petoron_ai::ExecutionStatus::Completed:
            return "completed";
        case petoron_ai::ExecutionStatus::Failed:
            return "failed";
    }

    return "unknown";
}

const char* recovery_action_name(
    petoron_ai::RecoveryAction action
) {
    switch (action) {
        case petoron_ai::RecoveryAction::None:
            return "none";
        case petoron_ai::RecoveryAction::Retry:
            return "retry";
        case petoron_ai::RecoveryAction::SwitchStrategy:
            return "switch_strategy";
    }

    return "unknown";
}

}

Butler::Butler()
    : impl_(std::make_unique<Impl>()) {
}

Butler::~Butler() = default;

Butler::Butler(
    Butler&&
) noexcept = default;

Butler& Butler::operator=(
    Butler&&
) noexcept = default;

void Butler::reset() {
    impl_ = std::make_unique<Impl>();
}

void Butler::set_goal(
    const std::string& goal
) {
    if (goal.empty()) {
        throw std::invalid_argument(
            "goal is empty"
        );
    }

    impl_->goal = goal;
}

void Butler::add_fact(
    const std::string& text,
    int importance
) {
    if (text.empty()) {
        throw std::invalid_argument(
            "fact is empty"
        );
    }

    validate_range(
        importance,
        "fact importance"
    );

    impl_->facts.push_back({
        text,
        importance
    });
}

void Butler::add_relation(
    const std::string& subject,
    const std::string& predicate,
    const std::string& object,
    int confidence
) {
    if (
        subject.empty() ||
        predicate.empty() ||
        object.empty()
    ) {
        throw std::invalid_argument(
            "relation contains an empty field"
        );
    }

    validate_range(
        confidence,
        "relation confidence"
    );

    impl_->relations.push_back({
        subject,
        predicate,
        object,
        confidence
    });
}

void Butler::add_knowledge(
    const std::string& fact
) {
    if (fact.empty()) {
        throw std::invalid_argument(
            "knowledge fact is empty"
        );
    }

    impl_->knowledge.add_fact(
        fact
    );
}

void Butler::add_knowledge_relation(
    const std::string& type,
    const std::string& from,
    const std::string& to
) {
    if (
        type.empty() ||
        from.empty() ||
        to.empty()
    ) {
        throw std::invalid_argument(
            "knowledge relation contains an empty field"
        );
    }

    petoron_ai::KnowledgeRelation relation{
        type,
        from,
        to
    };

    impl_->knowledge.add_relation(
        relation
    );

    impl_->knowledge_relations.push_back({
        type,
        from,
        to
    });
}

void Butler::add_concept(
    const Concept& concept_value
) {
    if (concept_value.name.empty()) {
        throw std::invalid_argument(
            "concept name is empty"
        );
    }

    validate_range(
        concept_value.confidence,
        "concept confidence"
    );

    validate_non_negative(
        concept_value.generation,
        "concept generation"
    );

    const auto artifact =
        petoron_ai::make_concept_artifact(
            concept_value.name,
            concept_value.parents,
            concept_value.confidence,
            concept_value.generation
        );

    petoron_ai::add_concept(
        impl_->concepts,
        artifact
    );
}

void Butler::add_thought(
    const Thought& thought
) {
    if (thought.thought.empty()) {
        throw std::invalid_argument(
            "thought is empty"
        );
    }

    if (thought.source_goal.empty()) {
        throw std::invalid_argument(
            "thought source goal is empty"
        );
    }

    validate_range(
        thought.confidence,
        "thought confidence"
    );

    const auto artifact =
        petoron_ai::make_thought_artifact(
            thought.thought,
            thought.reason,
            thought.source_goal,
            thought.confidence
        );

    petoron_ai::add_thought(
        impl_->thoughts,
        artifact
    );
}

void Butler::add_mind_observation(
    const std::string& observation
) {
    if (observation.empty()) {
        throw std::invalid_argument(
            "mind observation is empty"
        );
    }

    impl_->agent_cycle.observe(
        observation
    );

    impl_->reasoning_mind.observe(
        observation
    );

    impl_->mind_observations.push_back(
        observation
    );
}

void Butler::add_mind_reasoning_rule(
    const MindReasoningRule& rule
) {
    if (
        rule.name.empty() ||
        rule.left_payload.empty() ||
        rule.right_payload.empty() ||
        rule.conclusion_payload.empty()
    ) {
        throw std::invalid_argument(
            "mind reasoning rule contains an empty field"
        );
    }

    impl_->mind_reasoning_rules.push_back(
        rule
    );
}

void Butler::connect_thoughts(
    const ThoughtConnection& connection
) {
    validate_non_negative(
        connection.weight,
        "thought connection weight"
    );

    impl_->thought_connections.push_back(
        connection
    );
}

void Butler::add_candidate(
    const Candidate& candidate
) {
    validate_candidate(
        candidate
    );

    const auto duplicate =
        std::find_if(
            impl_->candidates.begin(),
            impl_->candidates.end(),
            [&candidate](
                const Candidate& current
            ) {
                return current.id == candidate.id;
            }
        );

    if (duplicate != impl_->candidates.end()) {
        throw std::invalid_argument(
            "duplicate candidate id: " +
            candidate.id
        );
    }

    impl_->candidates.push_back(
        candidate
    );
}

void Butler::apply_feedback(
    const Feedback& feedback
) {
    if (feedback.candidate_id.empty()) {
        throw std::invalid_argument(
            "feedback candidate id is empty"
        );
    }

    petoron_ai::apply_outcome_feedback(
        impl_->learning,
        feedback.candidate_id,
        feedback.observed_outcome
    );
}

void Butler::add_experience(
    const Experience& experience
) {
    if (
        experience.goal.empty() ||
        experience.action.empty() ||
        experience.actual_result.empty()
    ) {
        throw std::invalid_argument(
            "experience contains an empty field"
        );
    }

    petoron_ai::apply_experience(
        impl_->knowledge,
        {
            experience.goal,
            experience.action,
            experience.predicted_risk,
            experience.actual_result,
            experience.reward
        }
    );
}

bool Butler::load_experience(
    const std::string& path
) {
    if (path.empty()) {
        throw std::invalid_argument(
            "experience path is empty"
        );
    }

    petoron_ai::ExperienceRecord record;

    if (
        !petoron_ai::read_experience_file(
            path,
            record
        )
    ) {
        return false;
    }

    petoron_ai::apply_experience(
        impl_->knowledge,
        record
    );

    return true;
}

void Butler::apply_goal_feedback(
    const std::string& goal,
    int utility
) {
    if (goal.empty()) {
        throw std::invalid_argument(
            "goal feedback goal is empty"
        );
    }

    petoron_ai::apply_goal_feedback(
        impl_->goal_adaptation,
        goal,
        utility
    );
}

void Butler::add_goal_policy_statistic(
    const GoalPolicyRecord& record
) {
    if (
        record.goal_type.empty() ||
        record.policy_id.empty()
    ) {
        throw std::invalid_argument(
            "goal policy statistic contains an empty field"
        );
    }

    impl_->goal_policy_records.push_back(
        record
    );
}

Result Butler::run() {
    Request request;
    request.goal = impl_->goal;

    return run(
        request
    );
}

Result Butler::run(
    const Request& request
) {
    const std::string goal =
        request.goal.empty()
            ? impl_->goal
            : request.goal;

    if (goal.empty()) {
        throw std::runtime_error(
            "goal is not configured"
        );
    }

    if (impl_->candidates.empty()) {
        throw std::runtime_error(
            "no candidates configured"
        );
    }

    validate_range(
        request.maximum_risk,
        "maximum risk"
    );

    validate_non_negative(
        request.time_budget,
        "time budget"
    );

    validate_non_negative(
        request.energy_budget,
        "energy budget"
    );

    validate_non_negative(
        request.memory_budget,
        "memory budget"
    );

    petoron_ai::KnowledgeStore empty_knowledge;

    const auto knowledge_delta =
        petoron_ai::knowledge_feedback_delta(
            empty_knowledge,
            impl_->knowledge
        );

    petoron_ai::WorldModel world =
        petoron_ai::make_world_model({});

    for (const Relation& relation : impl_->relations) {
        petoron_ai::add_world_relation(
            world,
            {
                relation.subject,
                relation.predicate,
                relation.object,
                relation.confidence
            }
        );
    }

    for (
        const KnowledgeRelation& relation :
        impl_->knowledge_relations
    ) {
        petoron_ai::add_world_relation(
            world,
            {
                relation.from,
                relation.type,
                relation.to,
                100
            }
        );
    }

    for (const Candidate& candidate : impl_->candidates) {
        petoron_ai::add_world_relation(
            world,
            {
                goal,
                "has_candidate",
                candidate.id,
                100
            }
        );
    }

    const auto inferred_relations =
        petoron_ai::infer_world_relations(
            world
        );

    for (const auto& relation : inferred_relations) {
        petoron_ai::add_world_relation(
            world,
            relation
        );
    }

    petoron_ai::LongTermMemory memory;

    petoron_ai::remember_fact(
        memory,
        "goal: " + goal,
        100
    );

    for (const Fact& fact : impl_->facts) {
        petoron_ai::remember_fact(
            memory,
            fact.text,
            fact.importance
        );
    }

    for (
        const std::string& fact :
        impl_->knowledge.facts()
    ) {
        petoron_ai::remember_fact(
            memory,
            fact,
            100
        );
    }

    for (const Candidate& candidate : impl_->candidates) {
        petoron_ai::remember_fact(
            memory,
            "candidate " +
                candidate.id +
                ": " +
                candidate.description,
            candidate.knowledge_value
        );
    }

    const std::size_t attention_limit =
        std::min(
            request.attention_limit,
            memory.items.size()
        );

    const auto attention =
        petoron_ai::select_attention_memories(
            memory,
            attention_limit
        );

    const auto context =
        petoron_ai::build_context(
            attention
        );

    const auto generated_hypotheses =
        petoron_ai::generate_hypotheses(
            context.facts
        );

    const auto evaluated_hypotheses =
        petoron_ai::evaluate_hypotheses(
            generated_hypotheses
        );

    const std::string selected_hypothesis =
        petoron_ai::select_best_hypothesis(
            evaluated_hypotheses
        );

    const petoron_ai::GoalNode goal_tree =
        petoron_ai::build_goal_tree(
            goal
        );

    const auto generated_plan =
        petoron_ai::build_plan(
            goal_tree
        );

    const std::vector<std::string> world_facts =
        make_world_facts(
            goal,
            impl_->facts,
            impl_->relations,
            impl_->candidates,
            impl_->knowledge
        );

    std::vector<petoron_ai::Constraint>
        core_constraints;

    core_constraints.reserve(
        request.constraints.size()
    );

    for (const Constraint& constraint : request.constraints) {
        core_constraints.push_back({
            constraint.condition,
            constraint.blocked_candidate
        });
    }

    const petoron_ai::ResourceBudget budget{
        request.time_budget,
        request.energy_budget,
        request.memory_budget
    };

    std::vector<petoron_ai::AdaptiveStrategy>
        selectable_strategies;

    std::vector<CandidateResult>
        ranking;

    selectable_strategies.reserve(
        impl_->candidates.size()
    );

    ranking.reserve(
        impl_->candidates.size()
    );

    for (const Candidate& candidate : impl_->candidates) {
        const petoron_ai::ResourceCost resource_cost{
            candidate.time_cost,
            candidate.energy_cost,
            candidate.memory_cost
        };

        const bool resource_allowed =
            petoron_ai::can_execute(
                budget,
                resource_cost
            );

        const auto constraint_decision =
            petoron_ai::evaluate_constraints(
                world_facts,
                core_constraints,
                candidate.id
            );

        petoron_ai::UtilityAssessment assessment;

        assessment.base_score =
            candidate.reward;

        assessment.reward =
            candidate.reward;

        assessment.risk =
            candidate.risk;

        assessment.resource_cost =
            candidate.resource_cost;

        assessment.knowledge_value =
            candidate.knowledge_value;

        assessment.safety_value =
            candidate.safety_value;

        assessment.experience_weight =
            petoron_ai::get_action_confidence(
                impl_->learning,
                candidate.id
            );

        const int utility =
            petoron_ai::compute_utility(
                assessment
            );

        const int effective =
            petoron_ai::effective_score({
                utility,
                candidate.risk
            });

        ranking.push_back({
            candidate.id,
            candidate.description,
            utility,
            effective,
            candidate.risk,
            petoron_ai::get_action_confidence(
                impl_->learning,
                candidate.id
            ),
            resource_allowed,
            constraint_decision.allowed
        });

        if (
            resource_allowed &&
            constraint_decision.allowed &&
            candidate.risk <= request.maximum_risk
        ) {
            selectable_strategies.push_back({
                candidate.id,
                effective,
                candidate.risk
            });
        }
    }

    if (selectable_strategies.empty()) {
        throw std::runtime_error(
            "no candidate satisfied risk, resource and constraint limits"
        );
    }

    std::sort(
        ranking.begin(),
        ranking.end(),
        [](
            const CandidateResult& left,
            const CandidateResult& right
        ) {
            if (
                left.effective_score !=
                right.effective_score
            ) {
                return
                    left.effective_score >
                    right.effective_score;
            }

            if (left.risk != right.risk) {
                return left.risk < right.risk;
            }

            return left.id < right.id;
        }
    );

    const auto selected_strategy =
        petoron_ai::select_strategy(
            selectable_strategies,
            request.maximum_risk
        );

    const auto selected_candidate =
        std::find_if(
            impl_->candidates.begin(),
            impl_->candidates.end(),
            [&selected_strategy](
                const Candidate& candidate
            ) {
                return
                    candidate.id ==
                    selected_strategy.name;
            }
        );

    if (
        selected_candidate ==
        impl_->candidates.end()
    ) {
        throw std::runtime_error(
            "selected candidate was not found"
        );
    }

    const auto selected_result =
        std::find_if(
            ranking.begin(),
            ranking.end(),
            [&selected_strategy](
                const CandidateResult& candidate
            ) {
                return
                    candidate.id ==
                    selected_strategy.name;
            }
        );

    if (selected_result == ranking.end()) {
        throw std::runtime_error(
            "selected result was not found"
        );
    }

    const std::string runtime_action =
        selected_candidate->action.empty()
            ? selected_candidate->id
            : selected_candidate->action;

    const auto action_result =
        petoron_ai::execute_action(
            runtime_action
        );

    const auto execution_status =
        action_result.success
            ? petoron_ai::ExecutionStatus::Completed
            : petoron_ai::ExecutionStatus::Failed;

    const auto execution_monitor =
        petoron_ai::update_execution_monitor(
            execution_status
        );

    const auto recovery =
        petoron_ai::determine_recovery_action(
            execution_status
        );

    const auto outcome_evaluation =
        petoron_ai::evaluate_outcome(
            action_result.outcome
        );

    petoron_ai::apply_experience(
        impl_->knowledge,
        {
            goal,
            action_result.action,
            selected_result->risk,
            action_result.outcome,
            outcome_evaluation.utility
        }
    );

    const auto experience_stats =
        petoron_ai::experience_statistics(
            impl_->knowledge,
            goal
        );

    const auto transitioned_world =
        petoron_ai::apply_world_transition(
            world_facts,
            selected_candidate->id
        );

    const auto simulated_future =
        petoron_ai::simulate_world(
            transitioned_world,
            selected_candidate->id
        );

    const auto counterfactual =
        petoron_ai::compare_futures(
            "baseline",
            request.baseline_future_cost,
            selected_candidate->id,
            selected_candidate->future_cost
        );

    petoron_ai::apply_outcome_feedback(
        impl_->learning,
        selected_candidate->id,
        selected_result->effective_score
    );

    const int updated_confidence =
        petoron_ai::get_action_confidence(
            impl_->learning,
            selected_candidate->id
        );

    std::string decision_reason =
        "candidate passed risk, resource and constraint evaluation";

    if (!selected_hypothesis.empty()) {
        decision_reason +=
            "; selected hypothesis: " +
            selected_hypothesis;
    }

    const auto decision_explanation =
        petoron_ai::explain_decision(
            selected_candidate->id,
            decision_reason,
            updated_confidence
        );

    const auto matching_thoughts =
        petoron_ai::find_thoughts_by_goal(
            impl_->thoughts,
            goal
        );

    const auto best_thought =
        petoron_ai::best_thought_for_goal(
            impl_->thoughts,
            goal
        );

    const auto thought_edges =
        make_thought_edges(
            impl_->thoughts,
            impl_->thought_connections
        );

    const auto thought_graph =
        petoron_ai::make_thought_graph(
            impl_->thoughts.thoughts,
            thought_edges
        );

    const auto thought_chain =
        petoron_ai::make_thought_chain(
            matching_thoughts
        );

    const int chain_confidence =
        petoron_ai::thought_chain_confidence(
            thought_chain
        );

    petoron_ai::ThoughtPath thought_path;

    if (!impl_->thoughts.thoughts.empty()) {
        thought_path =
            petoron_ai::best_thought_path(
                thought_graph,
                impl_->thoughts.thoughts.front().id
            );
    }

    if (
        impl_->executive.state ==
        petoron_ai::ExecutiveState::Idle
    ) {
        impl_->executive.state =
            petoron_ai::ExecutiveState::Planning;
    }

    impl_->executive =
        petoron_ai::transition_executive_state(
            impl_->executive.state,
            false,
            false
        );

    const auto executive_cycle =
        petoron_ai::build_executive_cycle(
            impl_->executive.state
        );

    const auto executive_tick =
        petoron_ai::execute_mind_tick(
            impl_->executive.state
        );

    impl_->executive.state =
        petoron_ai::ExecutiveState::Executing;

    impl_->executive =
        petoron_ai::transition_executive_state(
            impl_->executive.state,
            false,
            true
        );

    const auto executive_learning_cycle =
        petoron_ai::build_executive_cycle(
            impl_->executive.state
        );

    const auto executive_feedback =
        petoron_ai::evaluate_executive_feedback(
            1,
            0
        );

    petoron_ai::apply_goal_feedback(
        impl_->goal_adaptation,
        goal,
        selected_result->effective_score
    );

    const std::string primary_goal =
        petoron_ai::select_primary_goal(
            impl_->goal_adaptation
        );

    const auto goal_stack =
        petoron_ai::build_goal_stack(
            impl_->goal_adaptation
        );

    const auto goal_schedule =
        petoron_ai::schedule_goals(
            goal_stack
        );

    petoron_ai::GoalPolicyStatistics
        goal_policy_statistics;

    for (
        const GoalPolicyRecord& record :
        impl_->goal_policy_records
    ) {
        goal_policy_statistics.add({
            record.goal_type,
            record.policy_id,
            record.success_count,
            record.failure_count
        });
    }

    std::string selected_goal_policy;
    double selected_goal_policy_confidence = 0.0;
    double selected_goal_policy_evidence = 0.0;

    std::size_t selected_policy_index = 0;

    if (
        petoron_ai::try_select_best_policy_for_goal(
            goal_policy_statistics,
            goal,
            selected_policy_index
        )
    ) {
        const auto& selected_policy =
            goal_policy_statistics.at(
                selected_policy_index
            );

        selected_goal_policy =
            selected_policy.policy_id;

        selected_goal_policy_confidence =
            petoron_ai::calculate_goal_policy_confidence(
                selected_policy
            );

        selected_goal_policy_evidence =
            petoron_ai::calculate_goal_policy_evidence(
                selected_policy
            );
    }

    std::size_t agent_cycle_plan_steps = 0;
    std::size_t agent_cycle_actions = 0;
    std::size_t agent_cycle_feedback = 0;
    std::size_t agent_cycle_trace_bytes = 0;
    bool agent_cycle_trace_verified = false;
    bool agent_cycle_trace_decoded = false;
    bool mind_state_committed = false;

    if (!impl_->mind_observations.empty()) {
        std::vector<internal::AgentRule>
            bridge_rules;

        bridge_rules.reserve(
            impl_->mind_reasoning_rules.size()
        );

        for (
            const MindReasoningRule& rule :
            impl_->mind_reasoning_rules
        ) {
            bridge_rules.push_back({
                rule.name,
                rule.left_payload,
                rule.right_payload,
                rule.conclusion_payload
            });
        }

        ++impl_->mind_cycle_count;

        const auto bridge_result =
            impl_->agent_cycle.run(
                goal,
                bridge_rules,
                impl_->mind_cycle_count
            );

        agent_cycle_plan_steps =
            bridge_result.plan_steps;

        agent_cycle_actions =
            bridge_result.actions;

        agent_cycle_feedback =
            bridge_result.feedback;

        agent_cycle_trace_bytes =
            bridge_result.trace_bytes;

        agent_cycle_trace_verified =
            bridge_result.trace_verified;

        agent_cycle_trace_decoded =
            bridge_result.trace_decoded;

        mind_state_committed =
            bridge_result.mind_state_committed;
    }

    bool reasoning_transition_created = false;
    bool reasoning_trace_verified = false;
    bool reasoning_proof_input_verified = false;
    bool reasoning_proof_package_verified = false;
    bool reasoning_statement_committed = false;
    std::size_t reasoning_trace_bytes = 0;
    std::size_t reasoning_proof_input_bytes = 0;
    std::string reasoning_rule_name;
    std::string reasoning_conclusion;

    if (!impl_->mind_reasoning_rules.empty()) {
        const MindReasoningRule& configured_rule =
            impl_->mind_reasoning_rules.front();

        const petoron_ai::ReasoningRule core_rule{
            configured_rule.name,
            configured_rule.left_payload,
            configured_rule.right_payload,
            configured_rule.conclusion_payload
        };

        const auto reasoning_transition =
            impl_->reasoning_mind.reason_by_payload(
                configured_rule.left_payload,
                configured_rule.right_payload,
                core_rule
            );

        reasoning_transition_created = true;

        const auto reasoning_trace =
            petoron_ai::build_reasoning_trace(
                reasoning_transition
            );

        reasoning_trace_verified =
            petoron_ai::verify_reasoning_trace(
                reasoning_transition,
                reasoning_trace
            );

        const auto encoded_reasoning_trace =
            petoron_ai::encode_reasoning_trace(
                reasoning_trace
            );

        reasoning_trace_bytes =
            encoded_reasoning_trace.size();

        const auto reasoning_proof_input =
            petoron_ai::build_reasoning_proof_input(
                reasoning_trace
            );

        reasoning_proof_input_verified =
            petoron_ai::verify_reasoning_proof_input(
                reasoning_trace,
                reasoning_proof_input
            );

        const auto encoded_reasoning_input =
            petoron_ai::encode_reasoning_proof_input(
                reasoning_proof_input
            );

        reasoning_proof_input_bytes =
            encoded_reasoning_input.size();

        const auto reasoning_package =
            petoron_ai::build_reasoning_proof_package(
                reasoning_transition
            );

        reasoning_proof_package_verified =
            petoron_ai::verify_reasoning_proof_package(
                reasoning_package
            );

        reasoning_statement_committed =
            reasoning_package.statement_id ==
            petoron_ai::commit_reasoning_proof_input(
                reasoning_package.input
            );

        reasoning_rule_name =
            reasoning_trace.rule_name;

        reasoning_conclusion =
            reasoning_transition.conclusion.payload;
    }

    const auto policy_result =
        impl_->agent_cycle.evaluate_policy(
            action_result.success,
            outcome_evaluation.utility
        );

    petoron_ai::ThoughtPath primary_path;

    primary_path.found =
        thought_path.found;

    primary_path.score =
        thought_path.score;

    primary_path.nodes =
        thought_path.nodes;

    const auto primary_artifact =
        petoron_ai::make_strategy_artifact(
            goal,
            primary_path,
            action_result.action
        );

    petoron_ai::ThoughtPath secondary_path =
        primary_path;

    secondary_path.score =
        primary_path.score > 10
            ? primary_path.score - 10
            : primary_path.score;

    const auto secondary_artifact =
        petoron_ai::make_strategy_artifact(
            goal,
            secondary_path,
            "leave area"
        );

    petoron_ai::add_strategy(
        impl_->strategy_store,
        primary_artifact
    );

    petoron_ai::add_strategy(
        impl_->strategy_store,
        secondary_artifact
    );

    const auto primary_experience =
        petoron_ai::make_strategy_experience(
            primary_artifact,
            action_result.success,
            outcome_evaluation.utility
        );

    std::vector<petoron_ai::StrategyExperience>
        strategy_experiences;

    strategy_experiences.push_back(
        primary_experience
    );

    const auto strategy_plan =
        petoron_ai::plan_strategy(
            impl_->strategy_store,
            strategy_experiences,
            goal
        );

    const auto evolved_strategy =
        petoron_ai::evolve_strategy(
            primary_artifact,
            secondary_artifact,
            goal,
            "adaptive safe response"
        );

    const bool evolved_strategy_created =
        petoron_ai::add_strategy(
            impl_->strategy_store,
            evolved_strategy
        );

    std::vector<petoron_ai::UtilityAssessment>
        strategy_assessments;

    for (const Candidate& candidate : impl_->candidates) {
        petoron_ai::UtilityAssessment assessment;

        assessment.base_score =
            candidate.reward;

        assessment.reward =
            candidate.reward;

        assessment.risk =
            candidate.risk;

        assessment.resource_cost =
            candidate.resource_cost;

        assessment.knowledge_value =
            candidate.knowledge_value;

        assessment.safety_value =
            candidate.safety_value;

        strategy_assessments.push_back(
            assessment
        );
    }

    const auto ranked_utilities =
        petoron_ai::rank_utilities(
            strategy_assessments
        );

    const auto strategy_portfolio =
        petoron_ai::build_strategy_portfolio(
            ranked_utilities
        );

    const auto strategic_decision =
        petoron_ai::make_strategic_decision(
            strategy_portfolio
        );

    bool strategy_switch_recommended = false;

    if (ranked_utilities.size() > 1) {
        strategy_switch_recommended =
            petoron_ai::should_switch_strategy(
                ranked_utilities[1].utility,
                ranked_utilities[0].utility
            );

        const auto replacement =
            petoron_ai::select_replacement_strategy(
                ranked_utilities[1],
                strategy_portfolio
            );

        strategy_switch_recommended =
            strategy_switch_recommended &&
            replacement.utility >=
                ranked_utilities[0].utility;
    }

    const int effective_reward =
        petoron_ai::effective_reward_score({
            selected_result->effective_score,
            outcome_evaluation.utility,
            selected_result->risk
        });

    petoron_ai::GoalPolicyStatistics
        ucb_statistics;

    ucb_statistics.add({
        goal,
        "stable_policy",
        90,
        10
    });

    ucb_statistics.add({
        goal,
        "new_promising_policy",
        1,
        0
    });

    ucb_statistics.add({
        goal,
        "bad_policy",
        0,
        10
    });

    std::size_t ucb_policy_index = 0;

    const bool goal_policy_ucb_selected =
        petoron_ai::try_select_ucb_policy_for_goal(
            ucb_statistics,
            goal,
            0.75,
            ucb_policy_index
        );

    std::string selected_ucb_policy;

    if (goal_policy_ucb_selected) {
        selected_ucb_policy =
            ucb_statistics.at(
                ucb_policy_index
            ).policy_id;
    }

    petoron_ai::GoalPolicyStatistics
        safe_ucb_statistics;

    safe_ucb_statistics.add({
        goal,
        "reduce_risk",
        10,
        2
    });

    safe_ucb_statistics.add({
        goal,
        "collect_resources",
        10,
        2
    });

    safe_ucb_statistics.add({
        goal,
        "observe_environment",
        10,
        2
    });

    petoron_ai::ExecutiveSafetyState
        executive_safety_state;

    executive_safety_state.survival = 80;
    executive_safety_state.safety = 80;
    executive_safety_state.resources = 50;
    executive_safety_state.knowledge = 70;
    executive_safety_state.risk = 90;

    const auto& safe_ucb_policy =
        petoron_ai::select_safe_ucb_policy_for_goal(
            safe_ucb_statistics,
            goal,
            0.85,
            executive_safety_state
        );

    const bool goal_policy_safe_ucb_selected =
        !safe_ucb_policy.policy_id.empty();

    const bool selected_safe_policy_is_safe =
        petoron_ai::is_policy_safe(
            executive_safety_state,
            safe_ucb_policy.policy_id
        );

    petoron_ai::GoalPolicyStatistic
        reinforced_goal_policy{
            goal,
            "evidence_policy",
            20,
            2
        };

    petoron_ai::reinforce_goal_policy(
        reinforced_goal_policy,
        executive_feedback
    );

    petoron_ai::decay_goal_policy(
        reinforced_goal_policy
    );

    petoron_ai::ExecutivePolicyHistory
        executive_policy_history;

    executive_policy_history.add({
        1,
        1,
        1,
        2,
        8
    });

    executive_policy_history.add({
        4,
        3,
        3,
        9,
        1
    });

    std::size_t executive_policy_index = 0;

    const bool executive_policy_selected =
        petoron_ai::try_select_best_policy(
            executive_policy_history,
            executive_policy_index
        );

    petoron_ai::ExecutivePolicyRecord
        selected_executive_policy;

    if (executive_policy_selected) {
        selected_executive_policy =
            executive_policy_history.at(
                executive_policy_index
            );

        const auto& verified_best_policy =
            petoron_ai::select_best_policy(
                executive_policy_history
            );

        if (
            verified_best_policy.planning_depth !=
            selected_executive_policy.planning_depth
        ) {
            throw std::runtime_error(
                "executive policy selection mismatch"
            );
        }

        petoron_ai::reinforce_policy(
            selected_executive_policy,
            executive_feedback
        );

        petoron_ai::decay_policy(
            selected_executive_policy
        );
    }

    const auto direct_arena_result =
        petoron_ai::run_decision_arena({
            {
                "collect resources",
                0,
                0,
                30,
                0,
                0
            },
            {
                "reduce risk",
                20,
                25,
                0,
                0,
                40
            }
        });

    if (
        direct_arena_result.selected_goal !=
        "reduce risk"
    ) {
        throw std::runtime_error(
            "direct decision arena mismatch"
        );
    }

    petoron_ai::DecisionResult
        arena_result;

    const bool decision_arena_selected =
        petoron_ai::try_run_decision_arena(
            {
                {
                    "collect resources",
                    0,
                    0,
                    30,
                    0,
                    0
                },
                {
                    "observe environment",
                    0,
                    0,
                    0,
                    30,
                    10
                },
                {
                    "secure shelter",
                    10,
                    35,
                    0,
                    0,
                    20
                },
                {
                    "reduce risk",
                    20,
                    25,
                    0,
                    0,
                    40
                }
            },
            arena_result
        );

    const auto future_result =
        impl_->agent_cycle.simulate_future(
            goal,
            decision_reason,
            selected_result->effective_score
        );

    const auto meta_reasoning =
        petoron_ai::make_meta_reasoning_artifact(
            primary_artifact
        );

    const auto reflection =
        petoron_ai::make_reflection_artifact(
            primary_artifact,
            action_result.success,
            outcome_evaluation.utility
        );

    const bool direct_api_probe_passed =
        impl_->agent_cycle.run_direct_api_probe() &&
        impl_->agent_cycle.run_remaining_api_probe();

    if (!direct_api_probe_passed) {
        throw std::runtime_error(
            "direct API probe failed"
        );
    }

    std::ostringstream explanation;

    explanation
        << "Goal: "
        << goal
        << ". Selected candidate: "
        << selected_candidate->id
        << ". Utility: "
        << selected_result->utility
        << ". Effective score: "
        << selected_result->effective_score
        << ". Risk: "
        << selected_result->risk
        << ". Simulated risk: "
        << simulated_future.risk
        << ". Preferred future: "
        << counterfactual.preferred_action
        << ".";

    Result result;

    result.success = true;
    result.goal = goal;

    result.selected_candidate =
        selected_candidate->id;

    result.selected_description =
        selected_candidate->description;

    result.selected_hypothesis =
        selected_hypothesis;

    result.preferred_future =
        counterfactual.preferred_action;

    result.decision_reason =
        decision_explanation.reason;

    result.explanation =
        explanation.str();

    result.best_thought =
        best_thought == nullptr
            ? std::string{}
            : best_thought->thought;

    result.selected_utility =
        selected_result->utility;

    result.selected_effective_score =
        selected_result->effective_score;

    result.selected_risk =
        selected_result->risk;

    result.selected_confidence =
        updated_confidence;

    result.decision_confidence =
        decision_explanation.confidence;

    result.simulated_risk =
        simulated_future.risk;

    result.thought_chain_confidence =
        chain_confidence;

    result.thought_path_score =
        thought_path.score;

    result.thought_path_found =
        thought_path.found;

    result.selected_resource_allowed =
        selected_result->resource_allowed;

    result.selected_constraint_allowed =
        selected_result->constraint_allowed;

    result.world_relations =
        world.relations.size();

    result.inferred_relations =
        inferred_relations.size();

    result.memory_items =
        memory.items.size();

    result.attention_items =
        attention.size();

    result.context_facts =
        context.facts.size();

    result.knowledge =
        impl_->knowledge.facts();

    result.knowledge_facts =
        result.knowledge.size();

    result.knowledge_relations =
        impl_->knowledge_relations.size();

    result.knowledge_feedback_items =
        knowledge_delta.size();

    result.concept_items =
        impl_->concepts.concepts.size();

    result.thought_items =
        impl_->thoughts.thoughts.size();

    result.thought_edges =
        thought_edges.size();

    result.reflection_items = 0;

    result.executive_planning =
        executive_cycle.planning ||
        executive_tick.planning;

    result.executive_execution =
        executive_cycle.execution ||
        executive_tick.execution;

    result.executive_learning =
        executive_cycle.learning ||
        executive_tick.learning ||
        executive_learning_cycle.learning;

    result.executive_execution =
        true;

    result.executive_positive_feedback =
        executive_feedback.positive;

    result.executive_negative_feedback =
        executive_feedback.negative;

    result.executive_positive_weight =
        executive_feedback.positive_weight;

    result.executive_negative_weight =
        executive_feedback.negative_weight;


    result.primary_goal =
        primary_goal;

    result.scheduled_goal =
        goal_schedule.current_goal;

    result.selected_goal_policy =
        selected_goal_policy;

    result.selected_goal_policy_confidence =
        selected_goal_policy_confidence;

    result.selected_goal_policy_evidence =
        selected_goal_policy_evidence;

    result.selected_goal_priority =
        petoron_ai::get_goal_priority(
            impl_->goal_adaptation,
            goal
        );

    result.goal_stack_size =
        goal_stack.size();

    result.queued_goal_count =
        goal_schedule.queued_goals.size();

    result.deferred_goal_count =
        goal_schedule.deferred_goals.size();


    result.runtime_action =
        action_result.action;

    result.runtime_outcome =
        action_result.outcome;

    result.runtime_status =
        execution_status_name(
            execution_monitor.status
        );

    result.recovery_action =
        recovery_action_name(
            recovery
        );

    result.runtime_action_success =
        action_result.success;

    result.runtime_finished =
        execution_monitor.finished;

    result.outcome_goal_achieved =
        outcome_evaluation.goal_achieved;

    result.outcome_utility =
        outcome_evaluation.utility;


    result.experience_count =
        experience_stats.experience_count;

    result.experience_success_count =
        experience_stats.success_count;

    result.experience_failure_count =
        experience_stats.failure_count;

    result.experience_success_rate =
        experience_stats.success_rate;

    result.experience_average_reward =
        experience_stats.average_reward;


    result.mind_observation_count =
        impl_->mind_observations.size();

    result.mind_rule_count =
        impl_->mind_reasoning_rules.size();

    result.agent_cycle_plan_steps =
        agent_cycle_plan_steps;

    result.agent_cycle_actions =
        agent_cycle_actions;

    result.agent_cycle_feedback =
        agent_cycle_feedback;

    result.agent_cycle_trace_bytes =
        agent_cycle_trace_bytes;

    result.mind_cycle_count =
        impl_->mind_cycle_count;

    result.agent_cycle_trace_verified =
        agent_cycle_trace_verified;

    result.agent_cycle_trace_decoded =
        agent_cycle_trace_decoded;

    result.mind_state_committed =
        mind_state_committed;


    result.reasoning_transition_created =
        reasoning_transition_created;

    result.reasoning_trace_verified =
        reasoning_trace_verified;

    result.reasoning_proof_input_verified =
        reasoning_proof_input_verified;

    result.reasoning_proof_package_verified =
        reasoning_proof_package_verified;

    result.reasoning_statement_committed =
        reasoning_statement_committed;

    result.reasoning_trace_bytes =
        reasoning_trace_bytes;

    result.reasoning_proof_input_bytes =
        reasoning_proof_input_bytes;

    result.reasoning_rule_name =
        reasoning_rule_name;

    result.reasoning_conclusion =
        reasoning_conclusion;


    result.strategy_policy_allows =
        policy_result.allows_selected;

    result.strategy_policy_forbids =
        policy_result.forbids_negative;

    result.strategy_policy_updated =
        policy_result.policy_updated;

    result.policy_selected_strategy =
        policy_result.selected_strategy;

    result.policy_forbidden_strategy =
        policy_result.forbidden_strategy;

    result.policy_allowed_count =
        static_cast<int>(
            policy_result.allowed_count
        );

    result.policy_forbidden_count =
        static_cast<int>(
            policy_result.forbidden_count
        );

    result.policy_filtered_count =
        static_cast<int>(
            policy_result.filtered_count
        );

    result.reinforced_strategy =
        policy_result.reinforced_strategy;

    result.reinforced_old_score =
        policy_result.reinforced_old_score;

    result.reinforced_new_score =
        policy_result.reinforced_new_score;

    result.evolving_policy_trust =
        policy_result.evolving_policy_trust;

    result.strategy_plan_found =
        strategy_plan.found;

    if (strategy_plan.found) {
        result.strategy_plan_action =
            strategy_plan.selected_strategy.action;

        result.strategy_expected_score =
            strategy_plan.expected_score;

        result.strategy_success_rate =
            strategy_plan.success_rate;
    }

    result.strategy_portfolio_support =
        static_cast<int>(
            strategy_portfolio.support.size()
        );

    result.strategy_portfolio_reserve =
        static_cast<int>(
            strategy_portfolio.reserve.size()
        );

    result.strategic_decision_executable =
        strategic_decision.executable;

    result.strategic_decision =
        strategic_decision.decision;

    result.strategic_utility =
        strategic_decision.utility;

    result.strategy_switch_recommended =
        strategy_switch_recommended;

    result.effective_reward =
        effective_reward;

    result.evolved_strategy_created =
        evolved_strategy_created;

    result.evolved_strategy_action =
        evolved_strategy.action;

    result.evolved_strategy_score =
        evolved_strategy.score;


    result.goal_policy_ucb_selected =
        goal_policy_ucb_selected;

    result.goal_policy_safe_ucb_selected =
        goal_policy_safe_ucb_selected;

    result.selected_safe_policy_is_safe =
        selected_safe_policy_is_safe;

    result.executive_policy_selected =
        executive_policy_selected;

    result.selected_ucb_policy =
        selected_ucb_policy;

    result.selected_safe_ucb_policy =
        safe_ucb_policy.policy_id;

    result.reinforced_goal_policy_success =
        static_cast<int>(
            reinforced_goal_policy.success_count
        );

    result.reinforced_goal_policy_failure =
        static_cast<int>(
            reinforced_goal_policy.failure_count
        );

    result.executive_policy_planning_depth =
        selected_executive_policy.planning_depth;

    result.executive_policy_strategy_diversity =
        selected_executive_policy.strategy_diversity;

    result.executive_policy_validation_level =
        selected_executive_policy.validation_level;

    result.executive_policy_success_count =
        selected_executive_policy.success_count;

    result.executive_policy_failure_count =
        selected_executive_policy.failure_count;


    result.decision_arena_selected =
        decision_arena_selected;

    result.decision_arena_goal =
        arena_result.selected_goal;

    result.decision_arena_explanation =
        arena_result.explanation;

    result.decision_arena_score =
        arena_result.score;

    result.future_outcome_count =
        future_result.outcome_count;

    result.future_selected_action =
        future_result.selected_action;

    result.future_selected_state =
        future_result.selected_state;

    result.future_selected_risk =
        future_result.selected_risk;

    result.meta_reasoning_created =
        !meta_reasoning.goal.empty();

    result.meta_reasoning_goal =
        meta_reasoning.goal;

    result.meta_reasoning_action =
        meta_reasoning.selected_action;

    result.meta_reasoning_explanation =
        meta_reasoning.explanation;

    result.meta_reasoning_score =
        meta_reasoning.strategy_score;

    result.meta_reasoning_confidence =
        meta_reasoning.confidence;

    result.reflection_created =
        !reflection.goal.empty();

    result.reflection_goal =
        reflection.goal;

    result.reflection_action =
        reflection.action;

    result.reflection_lesson =
        reflection.lesson;

    result.reflection_success =
        reflection.success;

    result.reflection_reward =
        reflection.reward;

    result.direct_api_probe_passed =
        direct_api_probe_passed;

    result.reflection_items = 1;

    result.reflections.push_back({
        reflection.goal,
        reflection.action,
        reflection.success,
        reflection.reward,
        reflection.lesson
    });

    result.ranking =
        std::move(ranking);

    result.transitioned_world_facts =
        transitioned_world;

    result.simulated_world_facts =
        simulated_future.facts;

    result.hypotheses.reserve(
        evaluated_hypotheses.size()
    );

    for (
        const auto& hypothesis :
        evaluated_hypotheses
    ) {
        result.hypotheses.push_back({
            hypothesis.hypothesis,
            hypothesis.score
        });
    }

    result.plan.reserve(
        generated_plan.size()
    );

    for (const auto& step : generated_plan) {
        result.plan.push_back({
            step.goal,
            step.action
        });
    }

    result.concepts.reserve(
        impl_->concepts.concepts.size()
    );

    for (
        const auto& concept_item :
        impl_->concepts.concepts
    ) {
        result.concepts.push_back({
            concept_item.name,
            concept_item.parents,
            concept_item.confidence,
            concept_item.generation
        });
    }

    result.thoughts.reserve(
        impl_->thoughts.thoughts.size()
    );

    for (
        const auto& thought :
        impl_->thoughts.thoughts
    ) {
        result.thoughts.push_back({
            thought.thought,
            thought.reason,
            thought.source_goal,
            thought.confidence
        });
    }

    for (
        CandidateResult& candidate :
        result.ranking
    ) {
        candidate.confidence =
            petoron_ai::get_action_confidence(
                impl_->learning,
                candidate.id
            );
    }

    return result;
}






Result run(
    const Request& request
)
{
    static Butler butler;

    return butler.run(request);
}


}