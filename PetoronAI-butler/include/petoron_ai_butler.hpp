/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace petoron_ai_butler {

struct Fact {
    std::string text;
    int importance = 0;
};

struct Relation {
    std::string subject;
    std::string predicate;
    std::string object;
    int confidence = 0;
};

struct KnowledgeRelation {
    std::string type;
    std::string from;
    std::string to;
};

struct Concept {
    std::string name;
    std::vector<std::string> parents;
    int confidence = 0;
    int generation = 0;
};

struct Thought {
    std::string thought;
    std::string reason;
    std::string source_goal;
    int confidence = 0;
};

struct ThoughtConnection {
    std::size_t from = 0;
    std::size_t to = 0;
    int weight = 0;
};

struct MindReasoningRule {
    std::string name;
    std::string left_payload;
    std::string right_payload;
    std::string conclusion_payload;
};

struct Constraint {
    std::string condition;
    std::string blocked_candidate;
};

struct Candidate {
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

struct Request {
    std::string goal;
    int maximum_risk = 100;
    int baseline_future_cost = 100;
    std::size_t attention_limit = 10;
    int time_budget = 100;
    int energy_budget = 100;
    int memory_budget = 100;
    std::vector<Constraint> constraints;
};

struct Feedback {
    std::string candidate_id;
    int observed_outcome = 0;
};

struct Experience {
    std::string goal;
    std::string action;
    int predicted_risk = 0;
    std::string actual_result;
    int reward = 0;
};

struct GoalPolicyRecord {
    std::string goal_type;
    std::string policy_id;
    std::size_t success_count = 0;
    std::size_t failure_count = 0;
};

struct CandidateResult {
    std::string id;
    std::string description;
    int utility = 0;
    int effective_score = 0;
    int risk = 0;
    int confidence = 0;
    bool resource_allowed = false;
    bool constraint_allowed = false;
};

struct HypothesisResult {
    std::string hypothesis;
    int score = 0;
};

struct PlanStep {
    std::string goal;
    std::string action;
};

struct StrategyResult {
    std::string strategy;
    int score = 0;
};

struct ConceptResult {
    std::string name;
    std::vector<std::string> parents;
    int confidence = 0;
    int generation = 0;
};

struct ThoughtResult {
    std::string thought;
    std::string reason;
    std::string source_goal;
    int confidence = 0;
};

struct ReflectionResult {
    std::string goal;
    std::string action;
    bool success = false;
    int reward = 0;
    std::string lesson;
};

struct Result {
    bool success = false;
    std::string goal;
    std::string selected_candidate;
    std::string selected_description;
    std::string selected_hypothesis;
    std::string preferred_future;
    std::string decision_reason;
    std::string explanation;
    std::string best_thought;
    int selected_utility = 0;
    int selected_effective_score = 0;
    int selected_risk = 0;
    int selected_confidence = 0;
    int decision_confidence = 0;
    int simulated_risk = 0;
    int thought_chain_confidence = 0;
    int thought_path_score = 0;
    bool thought_path_found = false;
    bool selected_resource_allowed = false;
    bool selected_constraint_allowed = false;
    std::size_t world_relations = 0;
    std::size_t inferred_relations = 0;
    std::size_t memory_items = 0;
    std::size_t attention_items = 0;
    std::size_t context_facts = 0;
    std::size_t knowledge_facts = 0;
    std::size_t knowledge_relations = 0;
    std::size_t knowledge_feedback_items = 0;
    std::size_t concept_items = 0;
    std::size_t thought_items = 0;
    std::size_t thought_edges = 0;
    std::size_t reflection_items = 0;
    bool executive_planning = false;
    bool executive_execution = false;
    bool executive_learning = false;
    bool executive_positive_feedback = false;
    bool executive_negative_feedback = false;
    std::size_t executive_positive_weight = 0;
    std::size_t executive_negative_weight = 0;
    std::string primary_goal;
    std::string scheduled_goal;
    std::string selected_goal_policy;
    double selected_goal_policy_confidence = 0.0;
    double selected_goal_policy_evidence = 0.0;
    int selected_goal_priority = 0;
    std::size_t goal_stack_size = 0;
    std::size_t queued_goal_count = 0;
    std::size_t deferred_goal_count = 0;
    std::string runtime_action;
    std::string runtime_outcome;
    std::string runtime_status;
    std::string recovery_action;
    bool runtime_action_success = false;
    bool runtime_finished = false;
    bool outcome_goal_achieved = false;
    int outcome_utility = 0;
    int experience_count = 0;
    int experience_success_count = 0;
    int experience_failure_count = 0;
    int experience_success_rate = 0;
    int experience_average_reward = 0;
    std::size_t mind_observation_count = 0;
    std::size_t mind_rule_count = 0;
    std::size_t agent_cycle_plan_steps = 0;
    std::size_t agent_cycle_actions = 0;
    std::size_t agent_cycle_feedback = 0;
    std::size_t agent_cycle_trace_bytes = 0;
    std::uint64_t mind_cycle_count = 0;
    bool agent_cycle_trace_verified = false;
    bool agent_cycle_trace_decoded = false;
    bool mind_state_committed = false;
    bool reasoning_transition_created = false;
    bool reasoning_trace_verified = false;
    bool reasoning_proof_input_verified = false;
    bool reasoning_proof_package_verified = false;
    bool reasoning_statement_committed = false;
    std::size_t reasoning_trace_bytes = 0;
    std::size_t reasoning_proof_input_bytes = 0;
    std::string reasoning_rule_name;
    std::string reasoning_conclusion;
    bool strategy_policy_allows = false;
    bool strategy_policy_forbids = false;
    bool strategy_policy_updated = false;
    bool strategy_plan_found = false;
    bool strategic_decision_executable = false;
    bool strategy_switch_recommended = false;
    bool evolved_strategy_created = false;
    std::string policy_selected_strategy;
    std::string policy_forbidden_strategy;
    std::string strategy_plan_action;
    std::string strategic_decision;
    std::string reinforced_strategy;
    std::string evolved_strategy_action;
    int policy_allowed_count = 0;
    int policy_forbidden_count = 0;
    int policy_filtered_count = 0;
    int reinforced_old_score = 0;
    int reinforced_new_score = 0;
    int evolving_policy_trust = 0;
    int strategy_expected_score = 0;
    int strategy_success_rate = 0;
    int strategy_portfolio_support = 0;
    int strategy_portfolio_reserve = 0;
    int strategic_utility = 0;
    int effective_reward = 0;
    int evolved_strategy_score = 0;
    bool goal_policy_ucb_selected = false;
    bool goal_policy_safe_ucb_selected = false;
    bool selected_safe_policy_is_safe = false;
    bool executive_policy_selected = false;
    std::string selected_ucb_policy;
    std::string selected_safe_ucb_policy;
    int reinforced_goal_policy_success = 0;
    int reinforced_goal_policy_failure = 0;
    int executive_policy_planning_depth = 0;
    int executive_policy_strategy_diversity = 0;
    int executive_policy_validation_level = 0;
    std::size_t executive_policy_success_count = 0;
    std::size_t executive_policy_failure_count = 0;
    bool decision_arena_selected = false;
    std::string decision_arena_goal;
    std::string decision_arena_explanation;
    int decision_arena_score = 0;

    std::size_t future_outcome_count = 0;
    std::string future_selected_action;
    std::string future_selected_state;
    int future_selected_risk = 0;

    bool meta_reasoning_created = false;
    std::string meta_reasoning_goal;
    std::string meta_reasoning_action;
    std::string meta_reasoning_explanation;
    int meta_reasoning_score = 0;
    int meta_reasoning_confidence = 0;

    bool reflection_created = false;
    std::string reflection_goal;
    std::string reflection_action;
    std::string reflection_lesson;
    bool reflection_success = false;
    int reflection_reward = 0;
    bool direct_api_probe_passed = false;
    std::vector<CandidateResult> ranking;
    std::vector<HypothesisResult> hypotheses;
    std::vector<PlanStep> plan;
    std::vector<ConceptResult> concepts;
    std::vector<ThoughtResult> thoughts;
    std::vector<ReflectionResult> reflections;
    std::vector<std::string> knowledge;
    std::vector<std::string> transitioned_world_facts;
    std::vector<std::string> simulated_world_facts;
};

class Butler {
public:
    Butler();
    ~Butler();

    Butler(const Butler&) = delete;
    Butler& operator=(const Butler&) = delete;

    Butler(Butler&&) noexcept;
    Butler& operator=(Butler&&) noexcept;

    void reset();

    void set_goal(
        const std::string& goal
    );

    void add_fact(
        const std::string& text,
        int importance
    );

    void add_relation(
        const std::string& subject,
        const std::string& predicate,
        const std::string& object,
        int confidence
    );

    void add_knowledge(
        const std::string& fact
    );

    void add_knowledge_relation(
        const std::string& type,
        const std::string& from,
        const std::string& to
    );

    void add_concept(
        const Concept& concept_value
    );

    void add_thought(
        const Thought& thought
    );

    void add_mind_observation(
        const std::string& observation
    );

    void add_mind_reasoning_rule(
        const MindReasoningRule& rule
    );

    void connect_thoughts(
        const ThoughtConnection& connection
    );

    void add_candidate(
        const Candidate& candidate
    );

    void apply_feedback(
        const Feedback& feedback
    );

    void add_experience(
        const Experience& experience
    );

    bool load_experience(
        const std::string& path
    );

    void apply_goal_feedback(
        const std::string& goal,
        int utility
    );

    void add_goal_policy_statistic(
        const GoalPolicyRecord& record
    );

    Result run();

    Result run(
        const Request& request
    );

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;



};


Result run(
    const Request& request
);


}
