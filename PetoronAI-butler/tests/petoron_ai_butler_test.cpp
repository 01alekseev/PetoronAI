/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai_butler.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        petoron_ai_butler::Butler butler;

        butler.set_goal(
            "avoid fire"
        );

        butler.add_goal_policy_statistic({
            "avoid fire",
            "evidence_policy",
            20,
            2
        });

        butler.add_goal_policy_statistic({
            "avoid fire",
            "experimental_policy",
            4,
            8
        });

        butler.add_fact(
            "independent validation required",
            100
        );

        butler.add_mind_observation(
            "fire is dangerous"
        );

        butler.add_mind_observation(
            "body is fire"
        );

        butler.add_mind_reasoning_rule({
            "fire_reasoning",
            "fire is dangerous",
            "body is fire",
            "avoid fire"
        });

        butler.add_fact(
            "maximize reliable knowledge",
            90
        );

        butler.add_knowledge(
            "experimental evidence is preferred"
        );

        butler.add_experience({
            "avoid fire",
            "find shelter",
            10,
            "safe shelter reached",
            100
        });

        butler.add_knowledge(
            "high risk requires stronger evidence"
        );

        butler.add_knowledge_relation(
            "supports",
            "experimental_data",
            "candidate_a"
        );

        butler.add_concept({
            "validated_strategy",
            {
                "strategy",
                "experimental_evidence"
            },
            95,
            1
        });

        butler.add_thought({
            "candidate_a has stronger evidence",
            "supported by experimental data",
            "avoid fire",
            95
        });

        butler.add_thought({
            "candidate_a has acceptable risk",
            "risk is below configured limit",
            "avoid fire",
            90
        });

        butler.connect_thoughts({
            0,
            1,
            90
        });

        butler.add_relation(
            "candidate_a",
            "supported_by",
            "experimental_data",
            95
        );

        butler.add_relation(
            "candidate_b",
            "supported_by",
            "simulation_only",
            60
        );

        butler.add_candidate({
            "candidate_a",
            "Evidence-supported candidate",
            "find shelter",
            90,
            10,
            10,
            90,
            90,
            20,
            10,
            10,
            10
        });

        butler.add_candidate({
            "candidate_b",
            "Experimental hypothesis",
            "leave area",
            95,
            25,
            15,
            80,
            70,
            30,
            20,
            20,
            20
        });

        petoron_ai_butler::Request request;

        request.goal =
            "avoid fire";

        request.maximum_risk = 50;
        request.baseline_future_cost = 100;
        request.attention_limit = 20;
        request.time_budget = 100;
        request.energy_budget = 100;
        request.memory_budget = 100;

        request.constraints.push_back({
            "block candidate_x",
            "candidate_x"
        });

        const auto result =
            butler.run(request);

        if (!result.direct_api_probe_passed) {
            throw std::runtime_error(
                "direct API probe failed"
            );
        }





        if (!result.success) {
            throw std::runtime_error(
                "result is not successful"
            );
        }

        if (result.selected_candidate.empty()) {
            throw std::runtime_error(
                "selected candidate is empty"
            );
        }

        if (result.selected_hypothesis.empty()) {
            throw std::runtime_error(
                "selected hypothesis is empty"
            );
        }

        if (result.knowledge_facts < 2) {
            throw std::runtime_error(
                "knowledge facts were not preserved"
            );
        }

        if (result.knowledge_relations != 1) {
            throw std::runtime_error(
                "unexpected knowledge relation count"
            );
        }

        if (result.knowledge_feedback_items == 0) {
            throw std::runtime_error(
                "knowledge feedback delta is empty"
            );
        }

        if (result.concept_items != 1) {
            throw std::runtime_error(
                "unexpected concept count"
            );
        }

        if (result.thought_items != 2) {
            throw std::runtime_error(
                "unexpected thought count"
            );
        }

        if (result.thought_edges != 1) {
            throw std::runtime_error(
                "unexpected thought edge count"
            );
        }

        if (result.best_thought.empty()) {
            throw std::runtime_error(
                "best thought is empty"
            );
        }

        if (result.thought_chain_confidence <= 0) {
            throw std::runtime_error(
                "invalid thought chain confidence"
            );
        }

        if (!result.thought_path_found) {
            throw std::runtime_error(
                "thought path was not found"
            );
        }

        if (
            result.primary_goal !=
            "avoid fire"
        ) {
            throw std::runtime_error(
                "unexpected primary goal"
            );
        }

        if (
            result.scheduled_goal !=
            "avoid fire"
        ) {
            throw std::runtime_error(
                "unexpected scheduled goal"
            );
        }

        if (
            result.selected_goal_policy !=
            "evidence_policy"
        ) {
            throw std::runtime_error(
                "unexpected selected goal policy"
            );
        }

        if (
            result.selected_goal_policy_confidence <= 0.0 ||
            result.selected_goal_policy_evidence <= 0.0
        ) {
            throw std::runtime_error(
                "invalid goal policy metrics"
            );
        }

        if (
            result.selected_goal_priority <= 0 ||
            result.goal_stack_size == 0
        ) {
            throw std::runtime_error(
                "goal adaptation is inactive"
            );
        }

        if (result.mind_observation_count != 2) {
            throw std::runtime_error(
                "unexpected mind observation count"
            );
        }

        if (result.mind_rule_count != 1) {
            throw std::runtime_error(
                "unexpected mind rule count"
            );
        }

        if (result.mind_cycle_count != 1) {
            throw std::runtime_error(
                "unexpected mind cycle count"
            );
        }

        if (!result.agent_cycle_trace_decoded) {
            throw std::runtime_error(
                "agent cycle trace was not decoded"
            );
        }

        if (!result.agent_cycle_trace_verified) {
            throw std::runtime_error(
                "agent cycle trace was not verified"
            );
        }

        if (result.agent_cycle_plan_steps == 0) {
            throw std::runtime_error(
                "agent cycle produced no plan"
            );
        }

        if (result.agent_cycle_actions == 0) {
            throw std::runtime_error(
                "agent cycle produced no actions"
            );
        }

        if (result.agent_cycle_feedback == 0) {
            throw std::runtime_error(
                "agent cycle produced no feedback"
            );
        }

        if (!result.mind_state_committed) {
            throw std::runtime_error(
                "mind state was not committed"
            );
        }

        if (!result.strategy_policy_allows) {
            throw std::runtime_error(
                "selected strategy is not policy allowed"
            );
        }

        if (!result.strategy_policy_forbids) {
            throw std::runtime_error(
                "negative strategy is not forbidden"
            );
        }

        if (
            result.policy_selected_strategy !=
            "find shelter"
        ) {
            throw std::runtime_error(
                "unexpected policy strategy"
            );
        }

        if (
            result.policy_forbidden_strategy !=
            "walk into storm"
        ) {
            throw std::runtime_error(
                "unexpected forbidden strategy"
            );
        }

        if (
            result.policy_allowed_count != 2 ||
            result.policy_forbidden_count != 1 ||
            result.policy_filtered_count != 2
        ) {
            throw std::runtime_error(
                "unexpected policy counts"
            );
        }

        if (!result.strategy_policy_updated) {
            throw std::runtime_error(
                "policy evolution was not updated"
            );
        }

        if (
            result.reinforced_new_score <=
            result.reinforced_old_score
        ) {
            throw std::runtime_error(
                "strategy was not reinforced"
            );
        }

        if (result.evolving_policy_trust <= 0) {
            throw std::runtime_error(
                "policy trust was not increased"
            );
        }

        if (!result.strategy_plan_found) {
            throw std::runtime_error(
                "strategy plan was not found"
            );
        }

        if (!result.strategic_decision_executable) {
            throw std::runtime_error(
                "strategic decision is not executable"
            );
        }

        if (
            result.strategic_decision !=
            "execute_primary_strategy"
        ) {
            throw std::runtime_error(
                "unexpected strategic decision"
            );
        }

        if (!result.evolved_strategy_created) {
            throw std::runtime_error(
                "evolved strategy was not created"
            );
        }

        if (result.effective_reward <= 0) {
            throw std::runtime_error(
                "effective reward is invalid"
            );
        }

        if (!result.goal_policy_ucb_selected) {
            throw std::runtime_error(
                "UCB goal policy was not selected"
            );
        }

        if (
            result.selected_ucb_policy !=
            "new_promising_policy"
        ) {
            throw std::runtime_error(
                "unexpected UCB goal policy"
            );
        }

        if (!result.goal_policy_safe_ucb_selected) {
            throw std::runtime_error(
                "safe UCB goal policy was not selected"
            );
        }

        if (!result.selected_safe_policy_is_safe) {
            throw std::runtime_error(
                "selected safe UCB policy is unsafe"
            );
        }

        if (
            result.selected_safe_ucb_policy ==
            "collect_resources"
        ) {
            throw std::runtime_error(
                "unsafe resource policy was selected"
            );
        }

        if (
            result.reinforced_goal_policy_success != 20 ||
            result.reinforced_goal_policy_failure != 1
        ) {
            throw std::runtime_error(
                "unexpected reinforced goal policy state"
            );
        }

        if (!result.executive_policy_selected) {
            throw std::runtime_error(
                "executive policy was not selected"
            );
        }

        if (
            result.executive_policy_planning_depth != 4 ||
            result.executive_policy_strategy_diversity != 3 ||
            result.executive_policy_validation_level != 3
        ) {
            throw std::runtime_error(
                "unexpected executive policy"
            );
        }

        if (
            result.executive_policy_success_count != 9 ||
            result.executive_policy_failure_count != 0
        ) {
            throw std::runtime_error(
                "unexpected reinforced executive policy state"
            );
        }

        if (!result.decision_arena_selected) {
            throw std::runtime_error(
                "decision arena did not select a goal"
            );
        }

        if (
            result.decision_arena_goal !=
            "reduce risk"
        ) {
            throw std::runtime_error(
                "unexpected decision arena goal"
            );
        }

        if (result.decision_arena_score <= 0) {
            throw std::runtime_error(
                "decision arena score is invalid"
            );
        }

        if (result.future_outcome_count != 2) {
            throw std::runtime_error(
                "unexpected future outcome count"
            );
        }

        if (
            result.future_selected_action !=
            "leave area"
        ) {
            throw std::runtime_error(
                "unexpected future action"
            );
        }

        if (
            result.future_selected_state !=
            "safe distance"
        ) {
            throw std::runtime_error(
                "unexpected future state"
            );
        }

        if (result.future_selected_risk != 10) {
            throw std::runtime_error(
                "unexpected future risk"
            );
        }

        if (!result.meta_reasoning_created) {
            throw std::runtime_error(
                "meta reasoning was not created"
            );
        }

        if (
            result.meta_reasoning_goal !=
            "avoid fire"
        ) {
            throw std::runtime_error(
                "unexpected meta reasoning goal"
            );
        }

        if (
            result.meta_reasoning_action !=
            "find shelter"
        ) {
            throw std::runtime_error(
                "unexpected meta reasoning action"
            );
        }

        if (
            result.meta_reasoning_explanation !=
            "selected strategy has verified thought path"
        ) {
            throw std::runtime_error(
                "unexpected meta reasoning explanation"
            );
        }

        if (!result.reflection_created) {
            throw std::runtime_error(
                "reflection was not created"
            );
        }

        if (!result.reflection_success) {
            throw std::runtime_error(
                "reflection did not record success"
            );
        }

        if (
            result.reflection_lesson !=
            "strategy should be reinforced"
        ) {
            throw std::runtime_error(
                "unexpected reflection lesson"
            );
        }

        if (result.reflection_items != 1) {
            throw std::runtime_error(
                "unexpected reflection count"
            );
        }

        if (!result.reasoning_transition_created) {
            throw std::runtime_error(
                "reasoning transition was not created"
            );
        }

        if (!result.reasoning_trace_verified) {
            throw std::runtime_error(
                "reasoning trace was not verified"
            );
        }

        if (!result.reasoning_proof_input_verified) {
            throw std::runtime_error(
                "reasoning proof input was not verified"
            );
        }

        if (!result.reasoning_proof_package_verified) {
            throw std::runtime_error(
                "reasoning proof package was not verified"
            );
        }

        if (!result.reasoning_statement_committed) {
            throw std::runtime_error(
                "reasoning statement was not committed"
            );
        }

        if (
            result.reasoning_trace_bytes == 0 ||
            result.reasoning_proof_input_bytes == 0
        ) {
            throw std::runtime_error(
                "reasoning proof encoding is empty"
            );
        }

        if (
            result.reasoning_rule_name !=
            "fire_reasoning"
        ) {
            throw std::runtime_error(
                "unexpected reasoning rule"
            );
        }

        if (
            result.reasoning_conclusion !=
            "avoid fire"
        ) {
            throw std::runtime_error(
                "unexpected reasoning conclusion"
            );
        }

        if (result.agent_cycle_trace_bytes == 0) {
            throw std::runtime_error(
                "agent cycle trace is empty"
            );
        }

        if (result.experience_count < 2) {
            throw std::runtime_error(
                "experience was not recorded"
            );
        }

        if (result.experience_success_count < 2) {
            throw std::runtime_error(
                "successful experience was not recorded"
            );
        }

        if (result.experience_failure_count != 0) {
            throw std::runtime_error(
                "unexpected failed experience"
            );
        }

        if (
            result.experience_success_rate <= 0 ||
            result.experience_average_reward <= 0
        ) {
            throw std::runtime_error(
                "invalid experience statistics"
            );
        }

        if (result.runtime_action.empty()) {
            throw std::runtime_error(
                "runtime action is empty"
            );
        }

        if (result.runtime_status.empty()) {
            throw std::runtime_error(
                "runtime status is empty"
            );
        }

        if (result.recovery_action.empty()) {
            throw std::runtime_error(
                "recovery action is empty"
            );
        }

        if (!result.runtime_finished) {
            throw std::runtime_error(
                "runtime monitor did not finish"
            );
        }

        if (!result.runtime_action_success) {
            throw std::runtime_error(
                "runtime action failed"
            );
        }

        if (
            result.runtime_status !=
            "completed"
        ) {
            throw std::runtime_error(
                "runtime status is not completed"
            );
        }

        if (
            result.recovery_action !=
            "none"
        ) {
            throw std::runtime_error(
                "unexpected recovery action"
            );
        }

        if (
            !result.executive_planning &&
            !result.executive_execution &&
            !result.executive_learning
        ) {
            throw std::runtime_error(
                "executive cycle is inactive"
            );
        }

        if (!result.executive_positive_feedback) {
            throw std::runtime_error(
                "executive feedback is not positive"
            );
        }

        if (result.plan.empty()) {
            throw std::runtime_error(
                "plan is empty"
            );
        }

        if (result.hypotheses.empty()) {
            throw std::runtime_error(
                "hypotheses are empty"
            );
        }

        if (result.transitioned_world_facts.empty()) {
            throw std::runtime_error(
                "transitioned world is empty"
            );
        }

        if (result.simulated_world_facts.empty()) {
            throw std::runtime_error(
                "simulated world is empty"
            );
        }

        std::cout
            << "=== PetoronAI Butler ===\n"
            << "goal="
            << result.goal
            << '\n'
            << "candidate="
            << result.selected_candidate
            << '\n'
            << "hypothesis="
            << result.selected_hypothesis
            << '\n'
            << "best_thought="
            << result.best_thought
            << '\n'
            << "knowledge_facts="
            << result.knowledge_facts
            << '\n'
            << "knowledge_relations="
            << result.knowledge_relations
            << '\n'
            << "knowledge_feedback_items="
            << result.knowledge_feedback_items
            << '\n'
            << "concept_items="
            << result.concept_items
            << '\n'
            << "thought_items="
            << result.thought_items
            << '\n'
            << "thought_edges="
            << result.thought_edges
            << '\n'
            << "thought_chain_confidence="
            << result.thought_chain_confidence
            << '\n'
            << "thought_path_found="
            << std::boolalpha
            << result.thought_path_found
            << '\n'
            << "thought_path_score="
            << result.thought_path_score
            << '\n'
            << "utility="
            << result.selected_utility
            << '\n'
            << "effective_score="
            << result.selected_effective_score
            << '\n'
            << "simulated_risk="
            << result.simulated_risk
            << '\n'
            << "executive_planning="
            << result.executive_planning
            << '\n'
            << "executive_execution="
            << result.executive_execution
            << '\n'
            << "executive_learning="
            << result.executive_learning
            << '\n'
            << "executive_positive_feedback="
            << result.executive_positive_feedback
            << '\n'
            << "executive_positive_weight="
            << result.executive_positive_weight
            << '\n'
            << "primary_goal="
            << result.primary_goal
            << '\n'
            << "scheduled_goal="
            << result.scheduled_goal
            << '\n'
            << "selected_goal_policy="
            << result.selected_goal_policy
            << '\n'
            << "goal_policy_confidence="
            << result.selected_goal_policy_confidence
            << '\n'
            << "goal_policy_evidence="
            << result.selected_goal_policy_evidence
            << '\n'
            << "goal_priority="
            << result.selected_goal_priority
            << '\n'
            << "goal_stack_size="
            << result.goal_stack_size
            << '\n'
            << "runtime_action="
            << result.runtime_action
            << '\n'
            << "runtime_outcome="
            << result.runtime_outcome
            << '\n'
            << "runtime_status="
            << result.runtime_status
            << '\n'
            << "runtime_success="
            << result.runtime_action_success
            << '\n'
            << "runtime_finished="
            << result.runtime_finished
            << '\n'
            << "recovery_action="
            << result.recovery_action
            << '\n'
            << "outcome_goal_achieved="
            << result.outcome_goal_achieved
            << '\n'
            << "outcome_utility="
            << result.outcome_utility
            << '\n'
            << "experience_count="
            << result.experience_count
            << '\n'
            << "experience_success_count="
            << result.experience_success_count
            << '\n'
            << "experience_failure_count="
            << result.experience_failure_count
            << '\n'
            << "experience_success_rate="
            << result.experience_success_rate
            << '\n'
            << "experience_average_reward="
            << result.experience_average_reward
            << '\n'
            << "mind_observation_count="
            << result.mind_observation_count
            << '\n'
            << "mind_rule_count="
            << result.mind_rule_count
            << '\n'
            << "mind_cycle_count="
            << result.mind_cycle_count
            << '\n'
            << "agent_cycle_plan_steps="
            << result.agent_cycle_plan_steps
            << '\n'
            << "agent_cycle_actions="
            << result.agent_cycle_actions
            << '\n'
            << "agent_cycle_feedback="
            << result.agent_cycle_feedback
            << '\n'
            << "agent_cycle_trace_bytes="
            << result.agent_cycle_trace_bytes
            << '\n'
            << "agent_cycle_trace_decoded="
            << result.agent_cycle_trace_decoded
            << '\n'
            << "agent_cycle_trace_verified="
            << result.agent_cycle_trace_verified
            << '\n'
            << "mind_state_committed="
            << result.mind_state_committed
            << '\n'
            << "reasoning_transition_created="
            << result.reasoning_transition_created
            << '\n'
            << "reasoning_rule_name="
            << result.reasoning_rule_name
            << '\n'
            << "reasoning_conclusion="
            << result.reasoning_conclusion
            << '\n'
            << "reasoning_trace_bytes="
            << result.reasoning_trace_bytes
            << '\n'
            << "reasoning_trace_verified="
            << result.reasoning_trace_verified
            << '\n'
            << "reasoning_proof_input_bytes="
            << result.reasoning_proof_input_bytes
            << '\n'
            << "reasoning_proof_input_verified="
            << result.reasoning_proof_input_verified
            << '\n'
            << "reasoning_proof_package_verified="
            << result.reasoning_proof_package_verified
            << '\n'
            << "reasoning_statement_committed="
            << result.reasoning_statement_committed
            << '\n'
            << "policy_selected_strategy="
            << result.policy_selected_strategy
            << '\n'
            << "policy_forbidden_strategy="
            << result.policy_forbidden_strategy
            << '\n'
            << "policy_allowed_count="
            << result.policy_allowed_count
            << '\n'
            << "policy_forbidden_count="
            << result.policy_forbidden_count
            << '\n'
            << "policy_filtered_count="
            << result.policy_filtered_count
            << '\n'
            << "strategy_policy_updated="
            << result.strategy_policy_updated
            << '\n'
            << "reinforced_strategy="
            << result.reinforced_strategy
            << '\n'
            << "reinforced_old_score="
            << result.reinforced_old_score
            << '\n'
            << "reinforced_new_score="
            << result.reinforced_new_score
            << '\n'
            << "evolving_policy_trust="
            << result.evolving_policy_trust
            << '\n'
            << "strategy_plan_found="
            << result.strategy_plan_found
            << '\n'
            << "strategy_plan_action="
            << result.strategy_plan_action
            << '\n'
            << "strategy_expected_score="
            << result.strategy_expected_score
            << '\n'
            << "strategy_success_rate="
            << result.strategy_success_rate
            << '\n'
            << "strategy_portfolio_support="
            << result.strategy_portfolio_support
            << '\n'
            << "strategy_portfolio_reserve="
            << result.strategy_portfolio_reserve
            << '\n'
            << "strategic_decision="
            << result.strategic_decision
            << '\n'
            << "strategic_utility="
            << result.strategic_utility
            << '\n'
            << "strategy_switch_recommended="
            << result.strategy_switch_recommended
            << '\n'
            << "effective_reward="
            << result.effective_reward
            << '\n'
            << "evolved_strategy_created="
            << result.evolved_strategy_created
            << '\n'
            << "evolved_strategy_action="
            << result.evolved_strategy_action
            << '\n'
            << "evolved_strategy_score="
            << result.evolved_strategy_score
            << '\n'
            << "goal_policy_ucb_selected="
            << result.goal_policy_ucb_selected
            << '\n'
            << "selected_ucb_policy="
            << result.selected_ucb_policy
            << '\n'
            << "goal_policy_safe_ucb_selected="
            << result.goal_policy_safe_ucb_selected
            << '\n'
            << "selected_safe_ucb_policy="
            << result.selected_safe_ucb_policy
            << '\n'
            << "selected_safe_policy_is_safe="
            << result.selected_safe_policy_is_safe
            << '\n'
            << "reinforced_goal_policy_success="
            << result.reinforced_goal_policy_success
            << '\n'
            << "reinforced_goal_policy_failure="
            << result.reinforced_goal_policy_failure
            << '\n'
            << "executive_policy_selected="
            << result.executive_policy_selected
            << '\n'
            << "executive_policy_planning_depth="
            << result.executive_policy_planning_depth
            << '\n'
            << "executive_policy_strategy_diversity="
            << result.executive_policy_strategy_diversity
            << '\n'
            << "executive_policy_validation_level="
            << result.executive_policy_validation_level
            << '\n'
            << "executive_policy_success_count="
            << result.executive_policy_success_count
            << '\n'
            << "executive_policy_failure_count="
            << result.executive_policy_failure_count
            << '\n'
            << "decision_arena_selected="
            << result.decision_arena_selected
            << '\n'
            << "decision_arena_goal="
            << result.decision_arena_goal
            << '\n'
            << "decision_arena_score="
            << result.decision_arena_score
            << '\n'
            << "future_outcome_count="
            << result.future_outcome_count
            << '\n'
            << "future_selected_action="
            << result.future_selected_action
            << '\n'
            << "future_selected_state="
            << result.future_selected_state
            << '\n'
            << "future_selected_risk="
            << result.future_selected_risk
            << '\n'
            << "meta_reasoning_created="
            << result.meta_reasoning_created
            << '\n'
            << "meta_reasoning_goal="
            << result.meta_reasoning_goal
            << '\n'
            << "meta_reasoning_action="
            << result.meta_reasoning_action
            << '\n'
            << "meta_reasoning_score="
            << result.meta_reasoning_score
            << '\n'
            << "meta_reasoning_confidence="
            << result.meta_reasoning_confidence
            << '\n'
            << "meta_reasoning_explanation="
            << result.meta_reasoning_explanation
            << '\n'
            << "reflection_created="
            << result.reflection_created
            << '\n'
            << "reflection_goal="
            << result.reflection_goal
            << '\n'
            << "reflection_action="
            << result.reflection_action
            << '\n'
            << "reflection_success="
            << result.reflection_success
            << '\n'
            << "reflection_reward="
            << result.reflection_reward
            << '\n'
            << "reflection_lesson="
            << result.reflection_lesson
            << '\n'
            << "direct_api_probe_passed="
            << result.direct_api_probe_passed
            << '\n'
            << "PASS PetoronAI Butler\n";

        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr
            << "FAIL:"
            << error.what()
            << '\n';

        return EXIT_FAILURE;
    }
}
