/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai_butler_agent_cycle.hpp"

#include "petoron_ai/agent_cycle.hpp"
#include "petoron_ai/future_simulator.hpp"
#include "petoron_ai/concept/concept_store.hpp"
#include "petoron_ai/cycle_file.hpp"
#include "petoron_ai/goal_resolver.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"
#include "petoron_ai/knowledge/knowledge_transition_file.hpp"
#include "petoron_ai/memory/context_relevance.hpp"
#include "petoron_ai/planning/decision_pipeline.hpp"
#include "petoron_ai/runtime_input.hpp"
#include "petoron_ai/runtime_input_codec.hpp"
#include "petoron_ai/state/mind_state_file.hpp"
#include "petoron_ai/state/mind_state_transition_verifier.hpp"
#include "petoron_ai/state/mind_state_verifier.hpp"
#include "petoron_ai/text/text_to_runtime_input.hpp"
#include "petoron_ai/thought/thought_store_file.hpp"

#include <filesystem>
#include <fstream>
#include "petoron_ai/executive/executive_analytics.hpp"
#include "petoron_ai/executive/executive_configuration.hpp"
#include "petoron_ai/executive/executive_feedback_integration.hpp"
#include "petoron_ai/executive/executive_goal_policy_mapping.hpp"
#include "petoron_ai/executive/executive_optimization.hpp"
#include "petoron_ai/executive/executive_policy.hpp"
#include "petoron_ai/executive/executive_runtime_configuration.hpp"
#include "petoron_ai/executive/executive_state_machine.hpp"
#include "petoron_ai/executive/executive_transition_log.hpp"
#include "petoron_ai/executive/goal_aware_policy_selection.hpp"
#include "petoron_ai/executive/goal_policy_ucb_selection.hpp"
#include "petoron_ai/goal/goal_arbitration.hpp"
#include "petoron_ai/goal/goal_coalition.hpp"
#include "petoron_ai/goal/goal_conflict_resolver.hpp"
#include "petoron_ai/knowledge/knowledge_feedback_delta.hpp"
#include "petoron_ai/knowledge/knowledge_mind_bridge.hpp"
#include "petoron_ai/memory/long_term_memory.hpp"
#include "petoron_ai/reasoning_trace_codec.hpp"
#include "petoron_ai/strategy/strategy_experience.hpp"
#include "petoron_ai/strategy/strategy_store.hpp"
#include "petoron_ai/thought/thought_graph.hpp"
#include "petoron_ai/world/world_goal_impact.hpp"
#include "petoron_ai/agent_cycle_trace.hpp"
#include "petoron_ai/agent_cycle_trace_codec.hpp"
#include "petoron_ai/agent_cycle_trace_decoder.hpp"
#include "petoron_ai/petoron_mind.hpp"
#include "petoron_ai/reasoning_rule.hpp"
#include "petoron_ai/policy/policy_action_filter.hpp"
#include "petoron_ai/policy/policy_engine.hpp"
#include "petoron_ai/policy/policy_evolution.hpp"
#include "petoron_ai/strategy/strategy_reinforcement.hpp"
#include "petoron_ai/strategy/strategy_scoring.hpp"
#include "petoron_ai/state/mind_state.hpp"

#include <stdexcept>
#include <utility>

namespace petoron_ai_butler::internal {

struct AgentCycleBridge::Impl {
    petoron_ai::PetoronMind mind;
    petoron_ai::EvolvingPolicy evolving_policy;
};

AgentCycleBridge::AgentCycleBridge()
    : impl_(new Impl()) {
}

AgentCycleBridge::~AgentCycleBridge() {
    delete impl_;
}

AgentCycleBridge::AgentCycleBridge(
    AgentCycleBridge&& other
) noexcept
    : impl_(std::exchange(other.impl_, nullptr)) {
}

AgentCycleBridge& AgentCycleBridge::operator=(
    AgentCycleBridge&& other
) noexcept {
    if (this != &other) {
        delete impl_;
        impl_ = std::exchange(other.impl_, nullptr);
    }

    return *this;
}

void AgentCycleBridge::observe(
    const std::string& observation
) {
    if (observation.empty()) {
        throw std::invalid_argument(
            "mind observation is empty"
        );
    }

    impl_->mind.observe(
        observation
    );
}

bool AgentCycleBridge::run_remaining_api_probe() {
    namespace fs = std::filesystem;

    const fs::path directory =
        fs::temp_directory_path() /
        "petoron_ai_butler_api_probe";

    std::error_code error;
    fs::remove_all(directory, error);
    error.clear();

    if (!fs::create_directories(directory, error) && error) {
        return false;
    }

    const fs::path input_path =
        directory / "input.paiin";

    const fs::path old_kb_path =
        directory / "old.pkb";

    const fs::path new_kb_path =
        directory / "new.pkb";

    const fs::path cycle_path =
        directory / "cycle.pcycle";

    const fs::path transition_path =
        directory / "transition.pkbt";

    const fs::path old_state_path =
        directory / "old.pms";

    const fs::path new_state_path =
        directory / "new.pms";

    const fs::path thought_path =
        directory / "thoughts.pts";

    {
        std::ofstream output(input_path);

        if (!output) {
            return false;
        }

        output
            << "PAIIN:1\n"
            << "goal:avoid danger\n"
            << "goal_candidate:avoid fire\n"
            << "observe:fire is visible\n"
            << "observe:fire is dangerous\n"
            << "rule:fire_rule|fire is visible|fire is dangerous|avoid fire\n";
    }

    petoron_ai::RuntimeInput input;

    if (
        !petoron_ai::read_runtime_input(
            input_path.string(),
            input
        )
    ) {
        return false;
    }

    const auto text_input =
        petoron_ai::text_to_runtime_input(
            "Fire is visible and dangerous"
        );

    const auto encoded_input =
        petoron_ai::encode_runtime_input(
            input
        );

    const auto input_id =
        petoron_ai::commit_runtime_input(
            input
        );

    if (
        encoded_input.empty() ||
        input_id == petoron_ai::MemoryDigest{}
    ) {
        return false;
    }

    petoron_ai::KnowledgeStore old_store;
    old_store.add_fact("fire is visible");
    old_store.add_fact("fire is dangerous");

    petoron_ai::KnowledgeStore new_store =
        old_store;

    new_store.add_fact(
        "safe distance is available"
    );

    if (
        !petoron_ai::write_knowledge_file(
            old_kb_path.string(),
            old_store
        )
    ) {
        return false;
    }

    if (
        !petoron_ai::write_knowledge_file(
            new_kb_path.string(),
            new_store
        )
    ) {
        return false;
    }

    petoron_ai::KnowledgeStore read_old_store;
    petoron_ai::KnowledgeStore read_new_store;

    if (
        !petoron_ai::read_knowledge_file(
            old_kb_path.string(),
            read_old_store
        ) ||
        !petoron_ai::read_knowledge_file(
            new_kb_path.string(),
            read_new_store
        )
    ) {
        return false;
    }

    const auto resolved_trace =
        petoron_ai::resolve_goal_trace(
            read_old_store,
            input
        );

    const auto resolved_goal =
        petoron_ai::resolve_goal(
            read_old_store,
            input
        );

    if (
        resolved_goal != "avoid fire" ||
        resolved_trace.resolved_goal !=
            resolved_goal
    ) {
        return false;
    }

    petoron_ai::Context context;

    context.facts.push_back(
        "storm is dangerous"
    );

    context.facts.push_back(
        "shelter reduces risk"
    );

    context.facts.push_back(
        "food exists"
    );

    const auto relevant_context =
        petoron_ai::select_relevant_context(
            context,
            "survive storm"
        );

    if (relevant_context.size() != 2) {
        return false;
    }

    const std::vector<petoron_ai::StrategyScore>
        strategy_scores{
            {"find shelter", 100},
            {"walk into storm", -100}
        };

    const auto policy =
        petoron_ai::build_policy(
            strategy_scores
        );

    const auto pipeline_result =
        petoron_ai::run_decision_pipeline(
            policy,
            strategy_scores,
            {
                "storm is dangerous",
                "shelter reduces risk"
            },
            {}
        );

    if (
        !pipeline_result.allowed ||
        pipeline_result.selected_strategy !=
            "find shelter"
    ) {
        return false;
    }

    petoron_ai::ThoughtStore thought_store;

    petoron_ai::add_thought(
        thought_store,
        petoron_ai::make_thought_artifact(
            "leave dangerous area",
            "distance reduces exposure",
            "avoid fire",
            95
        )
    );

    if (
        !petoron_ai::write_thought_store_file(
            thought_path.string(),
            thought_store
        )
    ) {
        return false;
    }

    petoron_ai::ThoughtStore loaded_thought_store;

    if (
        !petoron_ai::read_thought_store_file(
            thought_path.string(),
            loaded_thought_store
        )
    ) {
        return false;
    }

    if (loaded_thought_store.thoughts.size() != 1) {
        return false;
    }

    const auto old_kb_id =
        read_old_store.root();

    const auto new_kb_id =
        read_new_store.root();

    petoron_ai::AgentCycleTrace trace{};

    trace.input_id = input_id;
    trace.kb_id = old_kb_id;
    trace.start_root = old_kb_id;
    trace.final_root = new_kb_id;
    trace.goal_name = resolved_goal;
    trace.feedback_count = 1;

    if (
        !petoron_ai::write_cycle_file(
            cycle_path.string(),
            trace
        )
    ) {
        return false;
    }

    petoron_ai::CycleFile cycle_file;

    if (
        !petoron_ai::read_cycle_file(
            cycle_path.string(),
            cycle_file
        )
    ) {
        return false;
    }

    if (
        !petoron_ai::verify_cycle_file(
            cycle_file
        )
    ) {
        return false;
    }

    petoron_ai::KnowledgeTransitionFile
        transition{};

    transition.old_kb_id =
        old_kb_id;

    transition.input_id =
        input_id;

    transition.cycle_id =
        cycle_file.cycle_id;

    transition.feedback_commitment =
        petoron_ai::commit_knowledge_feedback_delta(
            read_old_store,
            read_new_store
        );

    transition.new_kb_id =
        new_kb_id;

    const auto transition_id =
        petoron_ai::commit_knowledge_transition_file(
            transition
        );

    const auto transition_chain_id =
        petoron_ai::commit_knowledge_transition_chain({
            transition
        });

    if (
        transition_id == petoron_ai::MemoryDigest{} ||
        transition_chain_id ==
            petoron_ai::MemoryDigest{}
    ) {
        return false;
    }

    if (
        !petoron_ai::write_knowledge_transition_file(
            transition_path.string(),
            transition
        )
    ) {
        return false;
    }

    petoron_ai::KnowledgeTransitionFile
        loaded_transition{};

    if (
        !petoron_ai::read_knowledge_transition_file(
            transition_path.string(),
            loaded_transition
        )
    ) {
        return false;
    }

    if (
        loaded_transition.new_kb_id !=
        transition.new_kb_id
    ) {
        return false;
    }

    if (
        !petoron_ai::verify_knowledge_transition_file(
            old_kb_path.string(),
            input_path.string(),
            cycle_path.string(),
            new_kb_path.string(),
            transition_path.string()
        )
    ) {
        return false;
    }

    petoron_ai::MindState old_state{};

    old_state.current_kb_id =
        old_kb_id;

    old_state.cycle_count = 0;

    petoron_ai::MindState new_state{};

    new_state.current_kb_id =
        new_kb_id;

    new_state.transition_chain_id =
        transition_chain_id;

    new_state.last_cycle_id =
        cycle_file.cycle_id;

    new_state.cycle_count = 1;

    if (
        !petoron_ai::write_mind_state_file(
            old_state_path.string(),
            old_state
        ) ||
        !petoron_ai::write_mind_state_file(
            new_state_path.string(),
            new_state
        )
    ) {
        return false;
    }

    petoron_ai::MindState
        loaded_old_state{};

    petoron_ai::MindState
        loaded_new_state{};

    if (
        !petoron_ai::read_mind_state_file(
            old_state_path.string(),
            loaded_old_state
        ) ||
        !petoron_ai::read_mind_state_file(
            new_state_path.string(),
            loaded_new_state
        )
    ) {
        return false;
    }

    if (
        !petoron_ai::verify_mind_state_transition(
            old_state_path.string(),
            transition_path.string(),
            new_state_path.string()
        )
    ) {
        return false;
    }

    if (
        !petoron_ai::verify_mind_state(
            new_kb_path.string(),
            new_state_path.string(),
            {
                transition_path.string()
            }
        )
    ) {
        return false;
    }

    const bool text_input_called =
        !text_input.goal.name.empty() ||
        !text_input.goal_candidates.empty() ||
        !text_input.observations.empty() ||
        !text_input.rules.empty();

    fs::remove_all(directory, error);

    return text_input_called;
}

bool AgentCycleBridge::run_direct_api_probe() {
    petoron_ai::MemoryNode left;
    left.type = "observation";
    left.payload = "fire is dangerous";

    petoron_ai::MemoryNode right;
    right.type = "observation";
    right.payload = "body is fire";

    const auto left_id =
        petoron_ai::commit_memory_node(left);

    petoron_ai::MemoryGraph graph;
    graph.nodes.push_back(left);
    graph.nodes.push_back(right);

    const auto graph_id =
        petoron_ai::commit_memory_graph(graph);

    const auto observation =
        petoron_ai::apply_observation(
            graph,
            "safe distance available"
        );

    if (
        !petoron_ai::verify_memory_transition(
            graph,
            observation
        )
    ) {
        return false;
    }

    const petoron_ai::ReasoningRule rule{
        "direct_fire_rule",
        "fire is dangerous",
        "body is fire",
        "avoid fire"
    };

    const auto reasoning =
        petoron_ai::apply_reasoning_rule(
            left,
            right,
            rule
        );

    if (!reasoning.valid) {
        return false;
    }

    const auto reasoning_transition =
        petoron_ai::apply_reasoning_transition(
            graph,
            left,
            right,
            rule
        );

    if (
        !petoron_ai::verify_reasoning_transition(
            graph,
            reasoning_transition
        )
    ) {
        return false;
    }

    const auto reasoning_trace =
        petoron_ai::build_reasoning_trace(
            reasoning_transition
        );

    const auto reasoning_trace_id =
        petoron_ai::commit_reasoning_trace(
            reasoning_trace
        );

    petoron_ai::PetoronMind mind;
    mind.observe("fire is dangerous");
    mind.observe("body is fire");

    const auto* found_left =
        mind.find_by_payload(
            "fire is dangerous"
        );

    const auto* found_right =
        mind.find_by_payload(
            "body is fire"
        );

    if (
        found_left == nullptr ||
        found_right == nullptr
    ) {
        return false;
    }

    const auto direct_reason =
        mind.reason(
            *found_left,
            *found_right,
            rule
        );

    petoron_ai::PetoronMind automatic_mind;
    automatic_mind.observe("fire is dangerous");
    automatic_mind.observe("body is fire");

    const auto automatic_reasoning =
        automatic_mind.autoreason({
            rule
        });

    if (automatic_reasoning.size() != 1) {
        return false;
    }

    const auto& mind_graph =
        automatic_mind.graph();

    if (mind_graph.nodes.empty()) {
        return false;
    }

    petoron_ai::Plan plan;
    plan.goal.name = "avoid fire";
    plan.steps.push_back({
        "avoid fire",
        "fire is dangerous"
    });

    const auto actions =
        petoron_ai::execute_plan(
            plan
        );

    if (
        actions.size() != 1 ||
        !actions.front().success
    ) {
        return false;
    }

    const auto feedback =
        petoron_ai::learn_from_actions(
            automatic_mind,
            actions
        );

    if (feedback.empty()) {
        return false;
    }

    petoron_ai::KnowledgeStore knowledge;
    knowledge.add_fact("fire");
    knowledge.add_fact("distance");

    const petoron_ai::KnowledgeRelation relation{
        "requires",
        "fire",
        "distance"
    };

    const auto relation_node =
        petoron_ai::make_relation_node(
            relation
        );

    if (
        relation_node.type != "relation" ||
        !knowledge.add_relation(relation) ||
        !knowledge.has_fact("fire") ||
        !knowledge.has_relation(relation) ||
        knowledge.relations_from("fire").size() != 1 ||
        knowledge.relations_to("distance").size() != 1 ||
        knowledge.graph().nodes.empty()
    ) {
        return false;
    }

    petoron_ai::KnowledgeStore previous_knowledge;
    previous_knowledge.add_fact("fire");

    const auto feedback_delta_id =
        petoron_ai::commit_knowledge_feedback_delta(
            previous_knowledge,
            knowledge
        );

    petoron_ai::PetoronMind knowledge_mind;

    petoron_ai::load_knowledge_into_mind(
        knowledge,
        knowledge_mind
    );

    if (
        knowledge_mind.find_by_payload("fire") ==
        nullptr
    ) {
        return false;
    }

    petoron_ai::LongTermMemory memory;

    petoron_ai::remember_fact(
        memory,
        "fire is dangerous",
        10
    );

    const auto* memory_item =
        petoron_ai::find_memory_item(
            memory,
            "fire is dangerous"
        );

    if (
        memory_item == nullptr ||
        memory_item->strength != 10
    ) {
        return false;
    }

    petoron_ai::ConceptStore concepts;

    const auto concept_item =
        petoron_ai::make_concept_artifact(
            "danger",
            {"fire"},
            90,
            1
        );

    petoron_ai::add_concept(
        concepts,
        concept_item
    );

    if (
        petoron_ai::find_concept(
            concepts,
            "danger"
        ) == nullptr
    ) {
        return false;
    }

    const auto thought_a =
        petoron_ai::make_thought_artifact(
            "fire exists",
            "fire is dangerous",
            "avoid fire",
            80
        );

    const auto thought_b =
        petoron_ai::make_thought_artifact(
            "leave area",
            "distance reduces risk",
            "avoid fire",
            90
        );

    const auto thought_graph =
        petoron_ai::make_thought_graph(
            {thought_a, thought_b},
            {
                {
                    thought_a.id,
                    thought_b.id,
                    90
                }
            }
        );

    if (
        !petoron_ai::has_thought_path(
            thought_graph,
            thought_a.id,
            thought_b.id
        )
    ) {
        return false;
    }

    const auto thought_path =
        petoron_ai::best_thought_path(
            thought_graph,
            thought_a.id
        );

    const auto strategy =
        petoron_ai::make_strategy_artifact(
            "avoid fire",
            thought_path,
            "leave area"
        );

    petoron_ai::StrategyStore strategies;

    petoron_ai::add_strategy(
        strategies,
        strategy
    );

    const auto* best_strategy =
        petoron_ai::best_strategy_for_goal(
            strategies,
            "avoid fire"
        );

    if (best_strategy == nullptr) {
        return false;
    }

    const auto successful_experience =
        petoron_ai::make_strategy_experience(
            strategy,
            true,
            100
        );

    const auto failed_experience =
        petoron_ai::make_strategy_experience(
            strategy,
            false,
            -50
        );

    const auto merged_experience =
        petoron_ai::merge_strategy_experience(
            successful_experience,
            failed_experience
        );

    if (
        petoron_ai::strategy_success_rate(
            merged_experience
        ) != 50
    ) {
        return false;
    }

    const auto world =
        petoron_ai::make_world_model({
            {
                "fire",
                "causes",
                "danger",
                90
            },
            {
                "fire",
                "requires",
                "distance",
                95
            }
        });

    if (
        petoron_ai::find_world_relations(
            world,
            "fire"
        ).size() != 2
    ) {
        return false;
    }

    petoron_ai::Goal safety_goal;
    safety_goal.name = "stay safe";

    const auto impacts =
        petoron_ai::evaluate_goal_impact(
            world,
            safety_goal
        );

    const auto strategy_scores =
        petoron_ai::score_strategies(
            impacts
        );

    if (strategy_scores.empty()) {
        return false;
    }


    petoron_ai::Goal safe_goal;
    safe_goal.name = "stay safe";

    petoron_ai::Goal resource_goal;
    resource_goal.name = "collect resources";

    const std::vector<petoron_ai::PrioritizedGoal>
        prioritized_goals{
            {safe_goal, 100},
            {resource_goal, 80}
        };

    const auto active_goal =
        petoron_ai::select_active_goal(
            prioritized_goals
        );

    const auto coalition =
        petoron_ai::build_goal_coalition(
            prioritized_goals,
            50
        );

    const auto conflict =
        petoron_ai::resolve_goal_conflict(
            prioritized_goals[0],
            prioritized_goals[1]
        );

    if (
        active_goal.goal.name != "stay safe" ||
        coalition.goals.size() != 2 ||
        conflict.winner != "stay safe"
    ) {
        return false;
    }

    petoron_ai::ExecutiveTransitionLog transition_log;

    transition_log.record(
        petoron_ai::ExecutiveState::Idle
    );

    transition_log.record(
        petoron_ai::ExecutiveState::Planning
    );

    transition_log.record(
        petoron_ai::ExecutiveState::Executing
    );

    transition_log.record(
        petoron_ai::ExecutiveState::Learning
    );

    if (
        transition_log.history().size() != 4
    ) {
        return false;
    }

    const auto analytics =
        petoron_ai::analyze_transitions(
            transition_log
        );

    petoron_ai::ExecutiveFeedback positive_feedback;
    positive_feedback.positive = true;
    positive_feedback.positive_weight = 1;

    const auto integrated_analytics =
        petoron_ai::integrate_executive_feedback(
            analytics,
            positive_feedback
        );

    const auto optimization =
        petoron_ai::optimize_executive_cycle(
            integrated_analytics
        );

    const auto executive_policy =
        petoron_ai::build_executive_policy(
            optimization
        );

    const auto configuration =
        petoron_ai::build_executive_configuration(
            executive_policy
        );

    const auto runtime_configuration =
        petoron_ai::apply_executive_configuration(
            configuration
        );

    const auto policy_mapping =
        petoron_ai::map_goal_to_policy(
            "safety"
        );

    const auto next_state =
        petoron_ai::next_executive_state(
            petoron_ai::ExecutiveState::Idle,
            false,
            false,
            false
        );

    if (
        runtime_configuration.planner_depth < 1 ||
        policy_mapping.preferred_planning_depth != 3 ||
        next_state !=
            petoron_ai::ExecutiveState::Planning
    ) {
        return false;
    }

    petoron_ai::GoalPolicyStatistics policy_statistics;

    policy_statistics.add({
        "safety",
        "policy_a",
        3,
        7
    });

    policy_statistics.add({
        "safety",
        "policy_b",
        9,
        1
    });

    const auto& best_goal_policy =
        petoron_ai::select_best_policy_for_goal(
            policy_statistics,
            "safety"
        );

    const auto& ucb_goal_policy =
        petoron_ai::select_ucb_policy_for_goal(
            policy_statistics,
            "safety",
            0.85
        );

    if (
        best_goal_policy.policy_id.empty() ||
        ucb_goal_policy.policy_id.empty()
    ) {
        return false;
    }

    return
        left_id != petoron_ai::MemoryDigest{} &&
        graph_id != petoron_ai::MemoryDigest{} &&
        reasoning_trace_id != petoron_ai::MemoryDigest{} &&
        feedback_delta_id != petoron_ai::MemoryDigest{} &&
        direct_reason.conclusion.payload == "avoid fire";
}

FutureBridgeResult AgentCycleBridge::simulate_future(
    const std::string& goal,
    const std::string& reason,
    int score
) {
    petoron_ai::GoalResolution resolution;

    resolution.resolved_goal = goal;
    resolution.resolved_reason = reason;
    resolution.resolved_score = score;

    const auto outcomes =
        petoron_ai::simulate_goal(
            resolution
        );

    FutureBridgeResult result;

    result.outcome_count =
        outcomes.size();

    if (outcomes.empty()) {
        return result;
    }

    const auto* safest =
        &outcomes.front();

    for (const auto& outcome : outcomes) {
        if (
            outcome.risk_score <
            safest->risk_score
        ) {
            safest = &outcome;
        }
    }

    result.selected_action =
        safest->action;

    result.selected_state =
        safest->future_state;

    result.selected_risk =
        safest->risk_score;

    return result;
}

PolicyBridgeResult AgentCycleBridge::evaluate_policy(
    bool success,
    int reward
) {
    const std::vector<petoron_ai::StrategyScore> scores{
        {"find shelter", 105},
        {"keep distance", 70},
        {"walk into storm", -110}
    };

    const auto policy =
        petoron_ai::build_policy(
            scores
        );

    const auto filtered =
        petoron_ai::filter_strategies(
            policy,
            scores
        );

    const auto selected =
        petoron_ai::select_best_strategy(
            filtered
        );

    PolicyBridgeResult result;

    result.allows_selected =
        petoron_ai::policy_allows(
            policy,
            selected.strategy
        );

    result.forbids_negative =
        petoron_ai::policy_forbids(
            policy,
            "walk into storm"
        );

    result.allowed_count =
        policy.allowed.size();

    result.forbidden_count =
        policy.forbidden.size();

    result.filtered_count =
        filtered.size();

    result.selected_strategy =
        selected.strategy;

    result.forbidden_strategy =
        "walk into storm";

    result.selected_score =
        selected.score;

    const petoron_ai::StrategyOutcome outcome{
        selected.strategy,
        success,
        reward
    };

    const auto reinforced =
        petoron_ai::reinforce_strategy(
            selected,
            outcome
        );

    result.policy_updated =
        petoron_ai::update_policy(
            impl_->evolving_policy,
            reinforced
        );

    result.reinforced_strategy =
        reinforced.strategy;

    result.reinforced_old_score =
        reinforced.old_score;

    result.reinforced_new_score =
        reinforced.new_score;

    if (
        const auto* entry =
            petoron_ai::find_policy_entry(
                impl_->evolving_policy,
                reinforced.strategy
            )
    ) {
        result.evolving_policy_trust =
            entry->trust;
    }

    return result;
}

AgentCycleBridgeResult AgentCycleBridge::run(
    const std::string& goal,
    const std::vector<AgentRule>& rules,
    std::uint64_t cycle_count
) {
    std::vector<petoron_ai::ReasoningRule>
        core_rules;

    core_rules.reserve(
        rules.size()
    );

    for (const AgentRule& rule : rules) {
        core_rules.push_back({
            rule.name,
            rule.left_payload,
            rule.right_payload,
            rule.conclusion_payload
        });
    }

    const petoron_ai::MemoryDigest start_root =
        impl_->mind.root();

    const petoron_ai::Goal cycle_goal{
        goal
    };

    const auto cycle_result =
        petoron_ai::run_cycle(
            impl_->mind,
            cycle_goal,
            core_rules
        );

    const petoron_ai::MemoryDigest input_id{};
    const petoron_ai::MemoryDigest kb_id{};

    const auto trace =
        petoron_ai::build_agent_cycle_trace(
            input_id,
            kb_id,
            start_root,
            cycle_goal,
            cycle_result
        );

    const auto encoded =
        petoron_ai::encode_agent_cycle_trace(
            trace
        );

    petoron_ai::AgentCycleTrace decoded{};

    const bool decoded_ok =
        petoron_ai::decode_agent_cycle_trace(
            encoded,
            decoded
        );

    const bool verified =
        decoded_ok &&
        petoron_ai::verify_agent_cycle_trace(
            input_id,
            kb_id,
            start_root,
            cycle_goal,
            cycle_result,
            decoded
        );

    petoron_ai::MindState state;

    state.current_kb_id =
        kb_id;

    state.transition_chain_id =
        petoron_ai::commit_agent_cycle_trace(
            trace
        );

    state.last_cycle_id =
        state.transition_chain_id;

    state.cycle_count =
        cycle_count;

    const auto first_commit =
        petoron_ai::commit_mind_state(
            state
        );

    const auto second_commit =
        petoron_ai::commit_mind_state(
            state
        );

    AgentCycleBridgeResult result;

    result.plan_steps =
        cycle_result.plan.steps.size();

    result.actions =
        cycle_result.actions.size();

    result.feedback =
        cycle_result.feedback.size();

    result.trace_bytes =
        encoded.size();

    result.trace_verified =
        verified;

    result.trace_decoded =
        decoded_ok;

    result.mind_state_committed =
        first_commit == second_commit;

    result.cycle_count =
        cycle_count;

    return result;
}

}
