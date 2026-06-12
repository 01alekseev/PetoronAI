cmake_minimum_required(VERSION 3.20)

project(PetoronAI VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ZKPETORON_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(zkPetoron-Core)

add_library(petoron_ai
    mind/src/memory_node.cpp
    mind/src/memory_graph.cpp
    mind/src/memory_transition.cpp
    mind/src/reasoning_rule.cpp
    mind/src/reasoning_transition.cpp
    mind/src/petoron_mind.cpp
    mind/src/reasoning_trace.cpp
    mind/src/reasoning_trace_codec.cpp
    mind/src/reasoning_proof_input.cpp
    mind/src/reasoning_proof_input_codec.cpp
    mind/src/reasoning_proof_package.cpp
    mind/src/goal_engine.cpp
    mind/src/action_engine.cpp
    mind/src/goal_resolver.cpp
    mind/src/future_simulator.cpp
    mind/src/experience/experience_file.cpp
    mind/src/experience/experience_engine.cpp
    mind/src/experience/experience_statistics.cpp
    mind/src/feedback_engine.cpp
    mind/src/agent_cycle.cpp
    mind/src/agent_cycle_trace.cpp
    mind/src/agent_cycle_trace_codec.cpp
    mind/src/agent_cycle_trace_decoder.cpp
    mind/src/cycle_file.cpp
    mind/src/runtime_input.cpp
    mind/src/text/text_to_runtime_input.cpp
    mind/src/runtime_input_codec.cpp
    mind/src/knowledge/knowledge_store.cpp
    mind/src/knowledge/knowledge_relation.cpp
    mind/src/knowledge/knowledge_mind_bridge.cpp
    mind/src/knowledge/knowledge_file.cpp
    mind/src/knowledge/knowledge_feedback_delta.cpp
    mind/src/knowledge/knowledge_transition_file.cpp
    mind/src/state/mind_state.cpp
    mind/src/state/mind_state_file.cpp
    mind/src/state/mind_state_verifier.cpp
    mind/src/state/mind_state_transition_verifier.cpp
    mind/src/planning/goal_tree.cpp
    mind/src/planning/planner.cpp
    mind/src/thought/thought_artifact.cpp
    mind/src/thought/thought_store_file.cpp
    mind/src/thought/thought_search.cpp
    mind/src/thought/thought_chain.cpp
    mind/src/thought/thought_graph.cpp
    mind/src/strategy/strategy_artifact.cpp
    mind/src/strategy/strategy_store.cpp
    mind/src/strategy/strategy_experience.cpp
    mind/src/strategy/strategy_planner.cpp
    mind/src/strategy/strategy_evolution.cpp
    mind/src/strategy/strategy_scoring.cpp
    mind/src/strategy/strategy_reinforcement.cpp
    mind/src/policy/policy_engine.cpp
    mind/src/policy/policy_evolution.cpp
    mind/src/policy/policy_action_filter.cpp
    mind/src/goal/goal_arbitration.cpp
    mind/src/goal/goal_coalition.cpp
    mind/src/goal/goal_conflict_resolver.cpp
    mind/src/goal/goal_adaptation.cpp
    mind/src/goal/goal_priority_selector.cpp
    mind/src/goal/goal_stack.cpp
    mind/src/goal/goal_scheduler.cpp
    mind/src/planning/resource_budget.cpp
    mind/src/strategy/adaptive_strategy_selector.cpp
    mind/src/strategy/risk_assessment.cpp
    mind/src/strategy/reward_assessment.cpp
    mind/src/strategy/utility_engine.cpp
    mind/src/strategy/utility_ranking.cpp
    mind/src/strategy/strategy_portfolio.cpp
    mind/src/strategy/strategy_switching.cpp
    mind/src/strategy/strategic_decision_engine.cpp
    mind/src/runtime/execution_monitor.cpp
    mind/src/runtime/execution_recovery.cpp
    mind/src/executive/executive_controller.cpp
    mind/src/executive/executive_cycle.cpp
    mind/src/executive/executive_orchestrator.cpp
    mind/src/executive/executive_state_machine.cpp
    mind/src/executive/executive_transition_log.cpp
    mind/src/executive/executive_analytics.cpp
    mind/src/executive/executive_optimization.cpp
    mind/src/executive/executive_policy.cpp
    mind/src/executive/executive_configuration.cpp
    mind/src/executive/executive_runtime_configuration.cpp
    mind/src/executive/executive_feedback.cpp
    mind/src/executive/executive_feedback_integration.cpp
    mind/src/executive/executive_policy_history.cpp
    mind/src/executive/executive_policy_selection.cpp
    mind/src/executive/executive_policy_reinforcement.cpp
    mind/src/executive/executive_policy_decay.cpp
    mind/src/executive/executive_goal_policy_mapping.cpp
    mind/src/executive/goal_policy_statistics.cpp
    mind/src/executive/goal_aware_policy_selection.cpp
    mind/src/executive/goal_policy_reinforcement.cpp
    mind/src/executive/goal_policy_decay.cpp
    mind/src/executive/goal_policy_confidence.cpp
    mind/src/executive/goal_policy_evidence.cpp
    mind/src/executive/goal_policy_ucb_selection.cpp
    mind/src/executive/goal_policy_safety_filter.cpp
    mind/src/executive/goal_policy_safe_ucb_selection.cpp
    mind/src/decision/decision_arena.cpp
    mind/src/planning/constraint_engine.cpp
    mind/src/planning/decision_pipeline.cpp
    mind/src/planning/decision_explanation.cpp
    mind/src/planning/decision_selector.cpp
    mind/src/runtime/action_execution.cpp
    mind/src/runtime/outcome_evaluation.cpp
    mind/src/experience/self_improvement.cpp
    mind/src/reasoning/counterfactual_reasoning.cpp
    mind/src/reasoning/hypothesis_generator.cpp
    mind/src/reasoning/hypothesis_evaluation.cpp
    mind/src/world/world_state_transition.cpp
    mind/src/world/world_simulation.cpp
    mind/src/memory/long_term_memory.cpp
    mind/src/memory/attention_engine.cpp
    mind/src/memory/context_builder.cpp
    mind/src/memory/context_relevance.cpp
    mind/src/reflection/reflection_artifact.cpp
    mind/src/concept/concept_artifact.cpp
    mind/src/concept/concept_store.cpp
    mind/src/world/world_model.cpp
    mind/src/world/world_reasoning.cpp
    mind/src/world/world_goal_impact.cpp
    mind/src/meta/meta_reasoning_artifact.cpp
    mind/src/thought/thought_store.cpp
)
target_include_directories(petoron_ai
    PUBLIC
        mind/include
        zkPetoron-Core
)

target_link_libraries(petoron_ai
    PUBLIC
        zkpetoron
)

function(petoron_ai_add_app target source)
    add_executable(${target}
        ${source}
    )

    target_include_directories(${target}
        PRIVATE
            apps
    )

    target_link_libraries(${target}
        PRIVATE
            petoron_ai
    )
endfunction()

function(petoron_ai_add_cpp_test target source labels)
    add_executable(${target}
        ${source}
    )

    target_include_directories(${target}
        PRIVATE
            tests
            apps
    )

    target_link_libraries(${target}
        PRIVATE
            petoron_ai
    )

    add_test(
        NAME ${target}
        COMMAND ${target}
    )

    set_tests_properties(${target}
        PROPERTIES
            LABELS "${labels}"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endfunction()

petoron_ai_add_app(petoron_ai_verify_cycle apps/petoron_ai_verify_cycle.cpp)
petoron_ai_add_app(petoron_ai_run_cycle apps/petoron_ai_run_cycle.cpp)
petoron_ai_add_app(petoron_ai_inspect_cycle apps/petoron_ai_inspect_cycle.cpp)
petoron_ai_add_app(petoron_ai_inspect_input apps/petoron_ai_inspect_input.cpp)
petoron_ai_add_app(petoron_ai_verify_cycle_input apps/petoron_ai_verify_cycle_input.cpp)
petoron_ai_add_app(petoron_ai_check apps/petoron_ai_check.cpp)
petoron_ai_add_app(petoron_ai_inspect_kb apps/petoron_ai_inspect_kb.cpp)
petoron_ai_add_app(petoron_ai_run_cycle_kb apps/petoron_ai_run_cycle_kb.cpp)
petoron_ai_add_app(petoron_ai_verify_cycle_kb_input apps/petoron_ai_verify_cycle_kb_input.cpp)
petoron_ai_add_app(petoron_ai_run_cycle_kb_update apps/petoron_ai_run_cycle_kb_update.cpp)
petoron_ai_add_app(petoron_ai_verify_kb_update apps/petoron_ai_verify_kb_update.cpp)
petoron_ai_add_app(petoron_ai_write_kb_transition apps/petoron_ai_write_kb_transition.cpp)
petoron_ai_add_app(petoron_ai_inspect_kb_transition apps/petoron_ai_inspect_kb_transition.cpp)
petoron_ai_add_app(petoron_ai_verify_kb_transition apps/petoron_ai_verify_kb_transition.cpp)
petoron_ai_add_app(petoron_ai_verify_kb_transition_chain apps/petoron_ai_verify_kb_transition_chain.cpp)
petoron_ai_add_app(petoron_ai_inspect_mind_state apps/petoron_ai_inspect_mind_state.cpp)
petoron_ai_add_app(petoron_ai_write_mind_state apps/petoron_ai_write_mind_state.cpp)
petoron_ai_add_app(petoron_ai_verify_mind_state apps/petoron_ai_verify_mind_state.cpp)
petoron_ai_add_app(petoron_ai_verify_mind_state_transition apps/petoron_ai_verify_mind_state_transition.cpp)
petoron_ai_add_app(petoron_ai_step apps/petoron_ai_step.cpp)
petoron_ai_add_app(petoron_ai_init_state apps/petoron_ai_init_state.cpp)
petoron_ai_add_app(petoron_ai_text_to_input apps/petoron_ai_text_to_input.cpp)
petoron_ai_add_app(petoron_ai_kb_to_text apps/petoron_ai_kb_to_text.cpp)
petoron_ai_add_app(petoron_ai_resolve_goal apps/petoron_ai_resolve_goal.cpp)
petoron_ai_add_app(petoron_ai_trace_goal apps/petoron_ai_trace_goal.cpp)
petoron_ai_add_app(petoron_ai_simulate_goal apps/petoron_ai_simulate_goal.cpp)
petoron_ai_add_app(petoron_ai_simulation_to_text apps/petoron_ai_simulation_to_text.cpp)
petoron_ai_add_app(petoron_ai_ask apps/petoron_ai_ask.cpp)
petoron_ai_add_app(petoron_ai_bench apps/petoron_ai_bench.cpp)
petoron_ai_add_app(petoron_ai_record_experience apps/petoron_ai_record_experience.cpp)
petoron_ai_add_app(petoron_ai_experience_stats apps/petoron_ai_experience_stats.cpp)
petoron_ai_add_app(petoron_ai_plan_goal apps/petoron_ai_plan_goal.cpp)

enable_testing()

petoron_ai_add_cpp_test(petoron_ai_selftest tests/petoron_ai_selftest.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_ask_experience_weight_test tests/petoron_ai_ask_experience_weight_test.cpp "experience;bridge")
petoron_ai_add_cpp_test(petoron_ai_ask_test tests/petoron_ai_ask_test.cpp "bridge")
petoron_ai_add_cpp_test(petoron_ai_auto_goal_test tests/petoron_ai_auto_goal_test.cpp "goal;reasoning")
petoron_ai_add_cpp_test(petoron_ai_contradiction_test tests/petoron_ai_contradiction_test.cpp "reasoning")
petoron_ai_add_cpp_test(petoron_ai_cycle_input_mismatch_test tests/petoron_ai_cycle_input_mismatch_test.cpp "runtime")
petoron_ai_add_cpp_test(petoron_ai_determinism_test tests/petoron_ai_determinism_test.cpp "runtime")
petoron_ai_add_cpp_test(petoron_ai_experience_learning_test tests/petoron_ai_experience_learning_test.cpp "experience")
petoron_ai_add_cpp_test(petoron_ai_experience_stats_test tests/petoron_ai_experience_stats_test.cpp "experience")
petoron_ai_add_cpp_test(petoron_ai_future_simulator_test tests/petoron_ai_future_simulator_test.cpp "simulation")
petoron_ai_add_cpp_test(petoron_ai_generic_hypothesis_test tests/petoron_ai_generic_hypothesis_test.cpp "reasoning")
petoron_ai_add_cpp_test(petoron_ai_generic_risk_test tests/petoron_ai_generic_risk_test.cpp "reasoning")
petoron_ai_add_cpp_test(petoron_ai_goal_resolver_experience_weight_test tests/petoron_ai_goal_resolver_experience_weight_test.cpp "experience;goal")
petoron_ai_add_cpp_test(petoron_ai_goal_resolver_fallback_test tests/petoron_ai_goal_resolver_fallback_test.cpp "goal")
petoron_ai_add_cpp_test(petoron_ai_goal_resolver_ranking_test tests/petoron_ai_goal_resolver_ranking_test.cpp "goal")
petoron_ai_add_cpp_test(petoron_ai_goal_resolver_strategy_score_test tests/petoron_ai_goal_resolver_strategy_score_test.cpp "goal")
petoron_ai_add_cpp_test(petoron_ai_goal_resolver_test tests/petoron_ai_goal_resolver_test.cpp "goal")
petoron_ai_add_cpp_test(petoron_ai_goal_stack_input_test tests/petoron_ai_goal_stack_input_test.cpp "goal")
petoron_ai_add_cpp_test(petoron_ai_goal_trace_test tests/petoron_ai_goal_trace_test.cpp "goal")
petoron_ai_add_cpp_test(petoron_ai_hypothesis_reasoning_test tests/petoron_ai_hypothesis_reasoning_test.cpp "reasoning")
petoron_ai_add_cpp_test(petoron_ai_init_state_test tests/petoron_ai_init_state_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_input_mutation_test tests/petoron_ai_input_mutation_test.cpp "security")
petoron_ai_add_cpp_test(petoron_ai_kb_cycle_test tests/petoron_ai_kb_cycle_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_kb_input_mismatch_test tests/petoron_ai_kb_input_mismatch_test.cpp "runtime")
petoron_ai_add_cpp_test(petoron_ai_kb_test tests/petoron_ai_kb_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_kb_transition_chain_test tests/petoron_ai_kb_transition_chain_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_kb_transition_cli_test tests/petoron_ai_kb_transition_cli_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_kb_transition_tamper_test tests/petoron_ai_kb_transition_tamper_test.cpp "security")
petoron_ai_add_cpp_test(petoron_ai_kb_update_fake_feedback_test tests/petoron_ai_kb_update_fake_feedback_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_kb_update_fake_new_test tests/petoron_ai_kb_update_fake_new_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_kb_update_test tests/petoron_ai_kb_update_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_kb_update_wrong_delta_test tests/petoron_ai_kb_update_wrong_delta_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_mind_state_cli_test tests/petoron_ai_mind_state_cli_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_mind_state_transition_test tests/petoron_ai_mind_state_transition_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_multi_risk_priority_test tests/petoron_ai_multi_risk_priority_test.cpp "reasoning")
petoron_ai_add_cpp_test(petoron_ai_plan_goal_test tests/petoron_ai_plan_goal_test.cpp "goal;planning")
petoron_ai_add_cpp_test(petoron_ai_recursive_reasoning_test tests/petoron_ai_recursive_reasoning_test.cpp "reasoning")
petoron_ai_add_cpp_test(petoron_ai_runtime_cycle_test tests/petoron_ai_runtime_cycle_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_runtime_input_negative_test tests/petoron_ai_runtime_input_negative_test.cpp "security")
petoron_ai_add_cpp_test(petoron_ai_second_cycle_learning_test tests/petoron_ai_second_cycle_learning_test.cpp "reasoning")
petoron_ai_add_cpp_test(petoron_ai_simulation_to_text_test tests/petoron_ai_simulation_to_text_test.cpp "simulation")
petoron_ai_add_cpp_test(petoron_ai_step_test tests/petoron_ai_step_test.cpp "core")
petoron_ai_add_cpp_test(petoron_ai_tamper_test tests/petoron_ai_tamper_test.cpp "security")
petoron_ai_add_cpp_test(petoron_ai_text_bridge_test tests/petoron_ai_text_bridge_test.cpp "bridge")
petoron_ai_add_cpp_test(petoron_ai_text_to_simulation_test tests/petoron_ai_text_to_simulation_test.cpp "simulation;bridge")
petoron_ai_add_cpp_test(petoron_ai_planner_test tests/petoron_ai_planner_test.cpp "planning")




add_executable(petoron_ai_thought_artifact_test
    tests/petoron_ai_thought_artifact_test.cpp
)

target_link_libraries(petoron_ai_thought_artifact_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_thought_artifact_test
    COMMAND $<TARGET_FILE:petoron_ai_thought_artifact_test>
)

set_tests_properties(
    petoron_ai_thought_artifact_test
    PROPERTIES LABELS "thought"
)

add_executable(petoron_ai_record_thought
    apps/petoron_ai_record_thought.cpp
)

target_include_directories(petoron_ai_record_thought
    PRIVATE
        apps
)

target_link_libraries(petoron_ai_record_thought
    PRIVATE
        petoron_ai
)

add_executable(petoron_ai_inspect_thought_store
    apps/petoron_ai_inspect_thought_store.cpp
)

target_link_libraries(petoron_ai_inspect_thought_store
    PRIVATE
        petoron_ai
)

add_executable(petoron_ai_thought_store_test
    tests/petoron_ai_thought_store_test.cpp
)

target_link_libraries(petoron_ai_thought_store_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_thought_store_test
    COMMAND $<TARGET_FILE:petoron_ai_thought_store_test>
)

set_tests_properties(
    petoron_ai_thought_store_test
    PROPERTIES
        LABELS "thought"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(petoron_ai_find_thought
    apps/petoron_ai_find_thought.cpp
)

target_include_directories(petoron_ai_find_thought
    PRIVATE
        apps
)

target_link_libraries(petoron_ai_find_thought
    PRIVATE
        petoron_ai
)


add_executable(petoron_ai_thought_search_test
    tests/petoron_ai_thought_search_test.cpp
)

target_link_libraries(petoron_ai_thought_search_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_thought_search_test
    COMMAND $<TARGET_FILE:petoron_ai_thought_search_test>
)

set_tests_properties(
    petoron_ai_thought_search_test
    PROPERTIES LABELS "thought"
)

add_executable(petoron_ai_ask_with_thoughts
    apps/petoron_ai_ask_with_thoughts.cpp
)

target_link_libraries(petoron_ai_ask_with_thoughts
    PRIVATE
        petoron_ai
)

add_executable(petoron_ai_ask_with_thoughts_test
    tests/petoron_ai_ask_with_thoughts_test.cpp
)

target_include_directories(petoron_ai_ask_with_thoughts_test
    PRIVATE
        tests
)

target_link_libraries(petoron_ai_ask_with_thoughts_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_ask_with_thoughts_test
    COMMAND $<TARGET_FILE:petoron_ai_ask_with_thoughts_test>
)

set_tests_properties(
    petoron_ai_ask_with_thoughts_test
    PROPERTIES
        LABELS "thought;bridge;simulation"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(petoron_ai_thought_chain_test
    tests/petoron_ai_thought_chain_test.cpp
)

target_link_libraries(petoron_ai_thought_chain_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_thought_chain_test
    COMMAND $<TARGET_FILE:petoron_ai_thought_chain_test>
)

set_tests_properties(
    petoron_ai_thought_chain_test
    PROPERTIES LABELS "thought"
)

add_executable(petoron_ai_thought_graph_test
    tests/petoron_ai_thought_graph_test.cpp
)

target_link_libraries(petoron_ai_thought_graph_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_thought_graph_test
    COMMAND $<TARGET_FILE:petoron_ai_thought_graph_test>
)

set_tests_properties(
    petoron_ai_thought_graph_test
    PROPERTIES LABELS "thought"
)

add_executable(petoron_ai_thought_path_test
    tests/petoron_ai_thought_path_test.cpp
)

target_link_libraries(petoron_ai_thought_path_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_thought_path_test
    COMMAND $<TARGET_FILE:petoron_ai_thought_path_test>
)

set_tests_properties(
    petoron_ai_thought_path_test
    PROPERTIES LABELS "thought"
)

add_executable(petoron_ai_strategy_artifact_test
    tests/petoron_ai_strategy_artifact_test.cpp
)

target_link_libraries(petoron_ai_strategy_artifact_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_strategy_artifact_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_artifact_test>
)

set_tests_properties(
    petoron_ai_strategy_artifact_test
    PROPERTIES LABELS "strategy"
)

add_executable(petoron_ai_strategy_store_test
    tests/petoron_ai_strategy_store_test.cpp
)

target_link_libraries(petoron_ai_strategy_store_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_strategy_store_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_store_test>
)

set_tests_properties(
    petoron_ai_strategy_store_test
    PROPERTIES LABELS "strategy"
)

add_executable(petoron_ai_meta_reasoning_artifact_test
    tests/petoron_ai_meta_reasoning_artifact_test.cpp
)

target_link_libraries(petoron_ai_meta_reasoning_artifact_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_meta_reasoning_artifact_test
    COMMAND $<TARGET_FILE:petoron_ai_meta_reasoning_artifact_test>
)

set_tests_properties(
    petoron_ai_meta_reasoning_artifact_test
    PROPERTIES LABELS "meta;strategy"
)

add_executable(petoron_ai_strategy_experience_test
    tests/petoron_ai_strategy_experience_test.cpp
)

target_link_libraries(petoron_ai_strategy_experience_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_strategy_experience_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_experience_test>
)

set_tests_properties(
    petoron_ai_strategy_experience_test
    PROPERTIES LABELS "strategy;experience"
)

add_executable(petoron_ai_strategy_planner_test
    tests/petoron_ai_strategy_planner_test.cpp
)

target_link_libraries(petoron_ai_strategy_planner_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_strategy_planner_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_planner_test>
)

set_tests_properties(
    petoron_ai_strategy_planner_test
    PROPERTIES LABELS "strategy;planning;experience"
)

add_executable(petoron_ai_reflection_artifact_test
    tests/petoron_ai_reflection_artifact_test.cpp
)

target_link_libraries(petoron_ai_reflection_artifact_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_reflection_artifact_test
    COMMAND $<TARGET_FILE:petoron_ai_reflection_artifact_test>
)

set_tests_properties(
    petoron_ai_reflection_artifact_test
    PROPERTIES LABELS "reflection;strategy;experience"
)

add_executable(petoron_ai_strategy_evolution_test
    tests/petoron_ai_strategy_evolution_test.cpp
)

target_link_libraries(petoron_ai_strategy_evolution_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_strategy_evolution_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_evolution_test>
)

set_tests_properties(
    petoron_ai_strategy_evolution_test
    PROPERTIES LABELS "strategy;experience;planning"
)

add_executable(petoron_ai_concept_artifact_test
    tests/petoron_ai_concept_artifact_test.cpp
)

target_link_libraries(petoron_ai_concept_artifact_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_concept_artifact_test
    COMMAND $<TARGET_FILE:petoron_ai_concept_artifact_test>
)

set_tests_properties(
    petoron_ai_concept_artifact_test
    PROPERTIES LABELS "concept"
)

add_executable(petoron_ai_world_model_test
    tests/petoron_ai_world_model_test.cpp
)

target_link_libraries(petoron_ai_world_model_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_world_model_test
    COMMAND $<TARGET_FILE:petoron_ai_world_model_test>
)

set_tests_properties(
    petoron_ai_world_model_test
    PROPERTIES LABELS "world;concept"
)

add_executable(petoron_ai_world_reasoning_test
    tests/petoron_ai_world_reasoning_test.cpp
)

target_link_libraries(petoron_ai_world_reasoning_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_world_reasoning_test
    COMMAND $<TARGET_FILE:petoron_ai_world_reasoning_test>
)

set_tests_properties(
    petoron_ai_world_reasoning_test
    PROPERTIES LABELS "world;reasoning"
)

add_executable(petoron_ai_world_goal_impact_test
    tests/petoron_ai_world_goal_impact_test.cpp
)

target_link_libraries(petoron_ai_world_goal_impact_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_world_goal_impact_test
    COMMAND $<TARGET_FILE:petoron_ai_world_goal_impact_test>
)

set_tests_properties(
    petoron_ai_world_goal_impact_test
    PROPERTIES LABELS "world;goal;reasoning"
)

add_executable(petoron_ai_strategy_scoring_test
    tests/petoron_ai_strategy_scoring_test.cpp
)

target_link_libraries(petoron_ai_strategy_scoring_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_strategy_scoring_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_scoring_test>
)

set_tests_properties(
    petoron_ai_strategy_scoring_test
    PROPERTIES LABELS "strategy;world;goal;reasoning"
)

add_executable(petoron_ai_strategy_reinforcement_test
    tests/petoron_ai_strategy_reinforcement_test.cpp
)

target_link_libraries(petoron_ai_strategy_reinforcement_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_strategy_reinforcement_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_reinforcement_test>
)

set_tests_properties(
    petoron_ai_strategy_reinforcement_test
    PROPERTIES LABELS "strategy;experience;planning"
)

add_executable(petoron_ai_policy_engine_test
    tests/petoron_ai_policy_engine_test.cpp
)

target_link_libraries(petoron_ai_policy_engine_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_policy_engine_test
    COMMAND $<TARGET_FILE:petoron_ai_policy_engine_test>
)

set_tests_properties(
    petoron_ai_policy_engine_test
    PROPERTIES LABELS "policy;strategy;planning"
)

add_executable(petoron_ai_policy_evolution_test
    tests/petoron_ai_policy_evolution_test.cpp
)

target_link_libraries(petoron_ai_policy_evolution_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_policy_evolution_test
    COMMAND $<TARGET_FILE:petoron_ai_policy_evolution_test>
)

set_tests_properties(
    petoron_ai_policy_evolution_test
    PROPERTIES LABELS "policy;strategy;experience;planning"
)

add_executable(petoron_ai_policy_action_filter_test
    tests/petoron_ai_policy_action_filter_test.cpp
)

target_link_libraries(petoron_ai_policy_action_filter_test
    PRIVATE
        petoron_ai
)

add_test(
    NAME petoron_ai_policy_action_filter_test
    COMMAND $<TARGET_FILE:petoron_ai_policy_action_filter_test>
)

set_tests_properties(
    petoron_ai_policy_action_filter_test
    PROPERTIES LABELS "policy;strategy;planning"
)


add_executable(petoron_ai_goal_arbitration_test
    tests/petoron_ai_goal_arbitration_test.cpp
)

target_link_libraries(
    petoron_ai_goal_arbitration_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_arbitration_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_arbitration_test>
)

set_tests_properties(
    petoron_ai_goal_arbitration_test
    PROPERTIES LABELS "goal;planning"
)


add_executable(petoron_ai_goal_coalition_test
    tests/petoron_ai_goal_coalition_test.cpp
)

target_link_libraries(
    petoron_ai_goal_coalition_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_coalition_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_coalition_test>
)

set_tests_properties(
    petoron_ai_goal_coalition_test
    PROPERTIES LABELS "goal;planning"
)


add_executable(petoron_ai_goal_conflict_resolver_test
    tests/petoron_ai_goal_conflict_resolver_test.cpp
)

target_link_libraries(
    petoron_ai_goal_conflict_resolver_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_conflict_resolver_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_conflict_resolver_test>
)

set_tests_properties(
    petoron_ai_goal_conflict_resolver_test
    PROPERTIES LABELS "goal;planning;reasoning"
)


add_executable(petoron_ai_constraint_engine_test
    tests/petoron_ai_constraint_engine_test.cpp
)

target_link_libraries(
    petoron_ai_constraint_engine_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_constraint_engine_test
    COMMAND $<TARGET_FILE:petoron_ai_constraint_engine_test>
)

set_tests_properties(
    petoron_ai_constraint_engine_test
    PROPERTIES LABELS "planning;reasoning;world"
)


add_executable(petoron_ai_decision_pipeline_test
    tests/petoron_ai_decision_pipeline_test.cpp
)

target_link_libraries(
    petoron_ai_decision_pipeline_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_decision_pipeline_test
    COMMAND $<TARGET_FILE:petoron_ai_decision_pipeline_test>
)

set_tests_properties(
    petoron_ai_decision_pipeline_test
    PROPERTIES LABELS "planning;strategy;policy;goal"
)


add_executable(petoron_ai_counterfactual_reasoning_test
    tests/petoron_ai_counterfactual_reasoning_test.cpp
)

target_link_libraries(
    petoron_ai_counterfactual_reasoning_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_counterfactual_reasoning_test
    COMMAND $<TARGET_FILE:petoron_ai_counterfactual_reasoning_test>
)

set_tests_properties(
    petoron_ai_counterfactual_reasoning_test
    PROPERTIES LABELS "reasoning;planning;simulation"
)


add_executable(petoron_ai_decision_explanation_test
    tests/petoron_ai_decision_explanation_test.cpp
)

target_link_libraries(
    petoron_ai_decision_explanation_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_decision_explanation_test
    COMMAND $<TARGET_FILE:petoron_ai_decision_explanation_test>
)

set_tests_properties(
    petoron_ai_decision_explanation_test
    PROPERTIES LABELS "planning;reasoning"
)


add_executable(petoron_ai_world_state_transition_test
    tests/petoron_ai_world_state_transition_test.cpp
)

target_link_libraries(
    petoron_ai_world_state_transition_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_world_state_transition_test
    COMMAND $<TARGET_FILE:petoron_ai_world_state_transition_test>
)

set_tests_properties(
    petoron_ai_world_state_transition_test
    PROPERTIES LABELS "world;simulation"
)


add_executable(petoron_ai_world_simulation_test
    tests/petoron_ai_world_simulation_test.cpp
)

target_link_libraries(
    petoron_ai_world_simulation_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_world_simulation_test
    COMMAND $<TARGET_FILE:petoron_ai_world_simulation_test>
)

set_tests_properties(
    petoron_ai_world_simulation_test
    PROPERTIES LABELS "world;simulation;reasoning"
)


add_executable(petoron_ai_long_term_memory_test
    tests/petoron_ai_long_term_memory_test.cpp
)

target_link_libraries(
    petoron_ai_long_term_memory_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_long_term_memory_test
    COMMAND $<TARGET_FILE:petoron_ai_long_term_memory_test>
)

set_tests_properties(
    petoron_ai_long_term_memory_test
    PROPERTIES LABELS "memory;experience;world"
)


add_executable(petoron_ai_attention_engine_test
    tests/petoron_ai_attention_engine_test.cpp
)

target_link_libraries(
    petoron_ai_attention_engine_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_attention_engine_test
    COMMAND $<TARGET_FILE:petoron_ai_attention_engine_test>
)

set_tests_properties(
    petoron_ai_attention_engine_test
    PROPERTIES LABELS "memory;reasoning"
)


add_executable(petoron_ai_context_builder_test
    tests/petoron_ai_context_builder_test.cpp
)

target_link_libraries(
    petoron_ai_context_builder_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_context_builder_test
    COMMAND $<TARGET_FILE:petoron_ai_context_builder_test>
)

set_tests_properties(
    petoron_ai_context_builder_test
    PROPERTIES LABELS "memory;reasoning;context"
)


add_executable(petoron_ai_context_relevance_test
    tests/petoron_ai_context_relevance_test.cpp
)

target_link_libraries(
    petoron_ai_context_relevance_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_context_relevance_test
    COMMAND $<TARGET_FILE:petoron_ai_context_relevance_test>
)

set_tests_properties(
    petoron_ai_context_relevance_test
    PROPERTIES LABELS "memory;context;reasoning"
)


add_executable(petoron_ai_hypothesis_generator_test
    tests/petoron_ai_hypothesis_generator_test.cpp
)

target_link_libraries(
    petoron_ai_hypothesis_generator_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_hypothesis_generator_test
    COMMAND $<TARGET_FILE:petoron_ai_hypothesis_generator_test>
)

set_tests_properties(
    petoron_ai_hypothesis_generator_test
    PROPERTIES LABELS "reasoning;planning;context"
)


add_executable(petoron_ai_hypothesis_evaluation_test
    tests/petoron_ai_hypothesis_evaluation_test.cpp
)

target_link_libraries(
    petoron_ai_hypothesis_evaluation_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_hypothesis_evaluation_test
    COMMAND $<TARGET_FILE:petoron_ai_hypothesis_evaluation_test>
)

set_tests_properties(
    petoron_ai_hypothesis_evaluation_test
    PROPERTIES LABELS "reasoning;planning;strategy"
)


add_executable(petoron_ai_decision_selector_test
    tests/petoron_ai_decision_selector_test.cpp
)

target_link_libraries(
    petoron_ai_decision_selector_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_decision_selector_test
    COMMAND $<TARGET_FILE:petoron_ai_decision_selector_test>
)

set_tests_properties(
    petoron_ai_decision_selector_test
    PROPERTIES LABELS "planning;reasoning;decision"
)


add_executable(petoron_ai_action_execution_test
    tests/petoron_ai_action_execution_test.cpp
)

target_link_libraries(
    petoron_ai_action_execution_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_action_execution_test
    COMMAND $<TARGET_FILE:petoron_ai_action_execution_test>
)

set_tests_properties(
    petoron_ai_action_execution_test
    PROPERTIES LABELS "runtime;experience"
)


add_executable(petoron_ai_outcome_evaluation_test
    tests/petoron_ai_outcome_evaluation_test.cpp
)

target_link_libraries(
    petoron_ai_outcome_evaluation_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_outcome_evaluation_test
    COMMAND $<TARGET_FILE:petoron_ai_outcome_evaluation_test>
)

set_tests_properties(
    petoron_ai_outcome_evaluation_test
    PROPERTIES LABELS "runtime;experience;evaluation"
)


add_executable(petoron_ai_self_improvement_test
    tests/petoron_ai_self_improvement_test.cpp
)

target_link_libraries(
    petoron_ai_self_improvement_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_self_improvement_test
    COMMAND $<TARGET_FILE:petoron_ai_self_improvement_test>
)

set_tests_properties(
    petoron_ai_self_improvement_test
    PROPERTIES LABELS "experience;strategy;learning"
)


add_executable(petoron_ai_goal_adaptation_test
    tests/petoron_ai_goal_adaptation_test.cpp
)

target_link_libraries(
    petoron_ai_goal_adaptation_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_adaptation_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_adaptation_test>
)

set_tests_properties(
    petoron_ai_goal_adaptation_test
    PROPERTIES LABELS "goal;experience;learning"
)


add_executable(petoron_ai_goal_priority_selector_test
    tests/petoron_ai_goal_priority_selector_test.cpp
)

target_link_libraries(
    petoron_ai_goal_priority_selector_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_priority_selector_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_priority_selector_test>
)

set_tests_properties(
    petoron_ai_goal_priority_selector_test
    PROPERTIES LABELS "goal;planning;strategy"
)


add_executable(petoron_ai_goal_stack_test
    tests/petoron_ai_goal_stack_test.cpp
)

target_link_libraries(
    petoron_ai_goal_stack_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_stack_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_stack_test>
)

set_tests_properties(
    petoron_ai_goal_stack_test
    PROPERTIES LABELS "goal;planning;strategy"
)


add_executable(petoron_ai_goal_scheduler_test
    tests/petoron_ai_goal_scheduler_test.cpp
)

target_link_libraries(
    petoron_ai_goal_scheduler_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_scheduler_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_scheduler_test>
)

set_tests_properties(
    petoron_ai_goal_scheduler_test
    PROPERTIES LABELS "goal;planning;scheduling"
)


add_executable(petoron_ai_resource_budget_test
    tests/petoron_ai_resource_budget_test.cpp
)

target_link_libraries(
    petoron_ai_resource_budget_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_resource_budget_test
    COMMAND $<TARGET_FILE:petoron_ai_resource_budget_test>
)

set_tests_properties(
    petoron_ai_resource_budget_test
    PROPERTIES LABELS "planning;resource;constraint"
)


add_executable(petoron_ai_adaptive_strategy_selector_test
    tests/petoron_ai_adaptive_strategy_selector_test.cpp
)

target_link_libraries(
    petoron_ai_adaptive_strategy_selector_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_adaptive_strategy_selector_test
    COMMAND $<TARGET_FILE:petoron_ai_adaptive_strategy_selector_test>
)

set_tests_properties(
    petoron_ai_adaptive_strategy_selector_test
    PROPERTIES LABELS "strategy;planning;resource"
)


add_executable(petoron_ai_risk_assessment_test
    tests/petoron_ai_risk_assessment_test.cpp
)

target_link_libraries(
    petoron_ai_risk_assessment_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_risk_assessment_test
    COMMAND $<TARGET_FILE:petoron_ai_risk_assessment_test>
)

set_tests_properties(
    petoron_ai_risk_assessment_test
    PROPERTIES LABELS "strategy;risk;planning"
)


add_executable(petoron_ai_reward_assessment_test
    tests/petoron_ai_reward_assessment_test.cpp
)

target_link_libraries(
    petoron_ai_reward_assessment_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_reward_assessment_test
    COMMAND $<TARGET_FILE:petoron_ai_reward_assessment_test>
)

set_tests_properties(
    petoron_ai_reward_assessment_test
    PROPERTIES LABELS "strategy;reward;planning"
)


add_executable(petoron_ai_utility_engine_test
    tests/petoron_ai_utility_engine_test.cpp
)

target_link_libraries(
    petoron_ai_utility_engine_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_utility_engine_test
    COMMAND $<TARGET_FILE:petoron_ai_utility_engine_test>
)

set_tests_properties(
    petoron_ai_utility_engine_test
    PROPERTIES LABELS "strategy;planning;utility"
)


add_executable(petoron_ai_utility_ranking_test
    tests/petoron_ai_utility_ranking_test.cpp
)

target_link_libraries(
    petoron_ai_utility_ranking_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_utility_ranking_test
    COMMAND $<TARGET_FILE:petoron_ai_utility_ranking_test>
)

set_tests_properties(
    petoron_ai_utility_ranking_test
    PROPERTIES LABELS "strategy;utility;planning"
)


add_executable(petoron_ai_strategy_portfolio_test
    tests/petoron_ai_strategy_portfolio_test.cpp
)

target_link_libraries(
    petoron_ai_strategy_portfolio_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_strategy_portfolio_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_portfolio_test>
)

set_tests_properties(
    petoron_ai_strategy_portfolio_test
    PROPERTIES LABELS "strategy;planning;portfolio"
)


add_executable(petoron_ai_strategy_switching_test
    tests/petoron_ai_strategy_switching_test.cpp
)

target_link_libraries(
    petoron_ai_strategy_switching_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_strategy_switching_test
    COMMAND $<TARGET_FILE:petoron_ai_strategy_switching_test>
)

set_tests_properties(
    petoron_ai_strategy_switching_test
    PROPERTIES LABELS "strategy;planning;adaptation"
)


add_executable(petoron_ai_strategic_decision_engine_test
    tests/petoron_ai_strategic_decision_engine_test.cpp
)

target_link_libraries(
    petoron_ai_strategic_decision_engine_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_strategic_decision_engine_test
    COMMAND $<TARGET_FILE:petoron_ai_strategic_decision_engine_test>
)

set_tests_properties(
    petoron_ai_strategic_decision_engine_test
    PROPERTIES LABELS "strategy;planning;decision"
)


add_executable(petoron_ai_execution_monitor_test
    tests/petoron_ai_execution_monitor_test.cpp
)

target_link_libraries(
    petoron_ai_execution_monitor_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_execution_monitor_test
    COMMAND $<TARGET_FILE:petoron_ai_execution_monitor_test>
)

set_tests_properties(
    petoron_ai_execution_monitor_test
    PROPERTIES LABELS "runtime;execution;monitoring"
)


add_executable(petoron_ai_execution_recovery_test
    tests/petoron_ai_execution_recovery_test.cpp
)

target_link_libraries(
    petoron_ai_execution_recovery_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_execution_recovery_test
    COMMAND $<TARGET_FILE:petoron_ai_execution_recovery_test>
)

set_tests_properties(
    petoron_ai_execution_recovery_test
    PROPERTIES LABELS "runtime;execution;recovery"
)


add_executable(petoron_ai_executive_controller_test
    tests/petoron_ai_executive_controller_test.cpp
)

target_link_libraries(
    petoron_ai_executive_controller_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_controller_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_controller_test>
)

set_tests_properties(
    petoron_ai_executive_controller_test
    PROPERTIES LABELS "executive;planning;runtime"
)


add_executable(petoron_ai_executive_cycle_test
    tests/petoron_ai_executive_cycle_test.cpp
)

target_link_libraries(
    petoron_ai_executive_cycle_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_cycle_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_cycle_test>
)

set_tests_properties(
    petoron_ai_executive_cycle_test
    PROPERTIES LABELS "executive;runtime;planning"
)


add_executable(petoron_ai_executive_orchestrator_test
    tests/petoron_ai_executive_orchestrator_test.cpp
)

target_link_libraries(
    petoron_ai_executive_orchestrator_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_orchestrator_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_orchestrator_test>
)

set_tests_properties(
    petoron_ai_executive_orchestrator_test
    PROPERTIES LABELS "executive;runtime;orchestrator"
)


add_executable(petoron_ai_executive_state_machine_test
    tests/petoron_ai_executive_state_machine_test.cpp
)

target_link_libraries(
    petoron_ai_executive_state_machine_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_state_machine_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_state_machine_test>
)

set_tests_properties(
    petoron_ai_executive_state_machine_test
    PROPERTIES LABELS "executive;runtime;state_machine"
)


add_executable(petoron_ai_executive_transition_log_test
    tests/petoron_ai_executive_transition_log_test.cpp
)

target_link_libraries(
    petoron_ai_executive_transition_log_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_transition_log_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_transition_log_test>
)

set_tests_properties(
    petoron_ai_executive_transition_log_test
    PROPERTIES LABELS "executive;runtime;transition_log"
)


add_executable(petoron_ai_executive_analytics_test
    tests/petoron_ai_executive_analytics_test.cpp
)

target_link_libraries(
    petoron_ai_executive_analytics_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_analytics_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_analytics_test>
)

set_tests_properties(
    petoron_ai_executive_analytics_test
    PROPERTIES LABELS "executive;analytics;runtime"
)


add_executable(petoron_ai_executive_optimization_test
    tests/petoron_ai_executive_optimization_test.cpp
)

target_link_libraries(
    petoron_ai_executive_optimization_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_optimization_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_optimization_test>
)

set_tests_properties(
    petoron_ai_executive_optimization_test
    PROPERTIES LABELS "executive;optimization;analytics"
)


add_executable(petoron_ai_executive_policy_test
    tests/petoron_ai_executive_policy_test.cpp
)

target_link_libraries(
    petoron_ai_executive_policy_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_policy_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_policy_test>
)

set_tests_properties(
    petoron_ai_executive_policy_test
    PROPERTIES LABELS "executive;policy;optimization"
)


add_executable(petoron_ai_executive_configuration_test
    tests/petoron_ai_executive_configuration_test.cpp
)

target_link_libraries(
    petoron_ai_executive_configuration_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_configuration_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_configuration_test>
)

set_tests_properties(
    petoron_ai_executive_configuration_test
    PROPERTIES LABELS "executive;configuration;policy"
)


add_executable(petoron_ai_executive_runtime_configuration_test
    tests/petoron_ai_executive_runtime_configuration_test.cpp
)

target_link_libraries(
    petoron_ai_executive_runtime_configuration_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_runtime_configuration_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_runtime_configuration_test>
)

set_tests_properties(
    petoron_ai_executive_runtime_configuration_test
    PROPERTIES LABELS "executive;runtime;configuration"
)


add_executable(petoron_ai_executive_feedback_test
    tests/petoron_ai_executive_feedback_test.cpp
)

target_link_libraries(
    petoron_ai_executive_feedback_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_feedback_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_feedback_test>
)

set_tests_properties(
    petoron_ai_executive_feedback_test
    PROPERTIES LABELS "executive;feedback;runtime"
)


add_executable(petoron_ai_executive_feedback_integration_test
    tests/petoron_ai_executive_feedback_integration_test.cpp
)

target_link_libraries(
    petoron_ai_executive_feedback_integration_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_feedback_integration_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_feedback_integration_test>
)

set_tests_properties(
    petoron_ai_executive_feedback_integration_test
    PROPERTIES LABELS "executive;feedback;analytics"
)


add_executable(petoron_ai_executive_policy_history_test
    tests/petoron_ai_executive_policy_history_test.cpp
)

target_link_libraries(
    petoron_ai_executive_policy_history_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_policy_history_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_policy_history_test>
)

set_tests_properties(
    petoron_ai_executive_policy_history_test
    PROPERTIES LABELS "executive;policy;history"
)


add_executable(petoron_ai_executive_policy_selection_test
    tests/petoron_ai_executive_policy_selection_test.cpp
)

target_link_libraries(
    petoron_ai_executive_policy_selection_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_policy_selection_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_policy_selection_test>
)

set_tests_properties(
    petoron_ai_executive_policy_selection_test
    PROPERTIES LABELS "executive;policy;selection"
)


add_executable(petoron_ai_executive_policy_reinforcement_test
    tests/petoron_ai_executive_policy_reinforcement_test.cpp
)

target_link_libraries(
    petoron_ai_executive_policy_reinforcement_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_policy_reinforcement_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_policy_reinforcement_test>
)

set_tests_properties(
    petoron_ai_executive_policy_reinforcement_test
    PROPERTIES LABELS "executive;policy;reinforcement"
)


add_executable(petoron_ai_executive_policy_decay_test
    tests/petoron_ai_executive_policy_decay_test.cpp
)

target_link_libraries(
    petoron_ai_executive_policy_decay_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_policy_decay_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_policy_decay_test>
)

set_tests_properties(
    petoron_ai_executive_policy_decay_test
    PROPERTIES LABELS "executive;policy;decay"
)


add_executable(petoron_ai_executive_goal_policy_mapping_test
    tests/petoron_ai_executive_goal_policy_mapping_test.cpp
)

target_link_libraries(
    petoron_ai_executive_goal_policy_mapping_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_executive_goal_policy_mapping_test
    COMMAND $<TARGET_FILE:petoron_ai_executive_goal_policy_mapping_test>
)

set_tests_properties(
    petoron_ai_executive_goal_policy_mapping_test
    PROPERTIES LABELS "executive;goal;policy"
)


add_executable(petoron_ai_goal_policy_statistics_test
    tests/petoron_ai_goal_policy_statistics_test.cpp
)

target_link_libraries(
    petoron_ai_goal_policy_statistics_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_policy_statistics_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_policy_statistics_test>
)

set_tests_properties(
    petoron_ai_goal_policy_statistics_test
    PROPERTIES LABELS "goal;policy;statistics"
)


add_executable(petoron_ai_goal_aware_policy_selection_test
    tests/petoron_ai_goal_aware_policy_selection_test.cpp
)

target_link_libraries(
    petoron_ai_goal_aware_policy_selection_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_aware_policy_selection_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_aware_policy_selection_test>
)

set_tests_properties(
    petoron_ai_goal_aware_policy_selection_test
    PROPERTIES LABELS "goal;policy;selection"
)


add_executable(petoron_ai_goal_policy_reinforcement_test
    tests/petoron_ai_goal_policy_reinforcement_test.cpp
)

target_link_libraries(
    petoron_ai_goal_policy_reinforcement_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_policy_reinforcement_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_policy_reinforcement_test>
)

set_tests_properties(
    petoron_ai_goal_policy_reinforcement_test
    PROPERTIES LABELS "goal;policy;reinforcement"
)


add_executable(petoron_ai_goal_policy_decay_test
    tests/petoron_ai_goal_policy_decay_test.cpp
)

target_link_libraries(
    petoron_ai_goal_policy_decay_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_policy_decay_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_policy_decay_test>
)

set_tests_properties(
    petoron_ai_goal_policy_decay_test
    PROPERTIES LABELS "goal;policy;decay"
)


add_executable(petoron_ai_goal_policy_confidence_test
    tests/petoron_ai_goal_policy_confidence_test.cpp
)

target_link_libraries(
    petoron_ai_goal_policy_confidence_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_policy_confidence_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_policy_confidence_test>
)

set_tests_properties(
    petoron_ai_goal_policy_confidence_test
    PROPERTIES LABELS "goal;policy;confidence"
)


add_executable(petoron_ai_goal_policy_evidence_test
    tests/petoron_ai_goal_policy_evidence_test.cpp
)

target_link_libraries(
    petoron_ai_goal_policy_evidence_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_goal_policy_evidence_test
    COMMAND $<TARGET_FILE:petoron_ai_goal_policy_evidence_test>
)

set_tests_properties(
    petoron_ai_goal_policy_evidence_test
    PROPERTIES LABELS "goal;policy;evidence"
)


petoron_ai_add_cpp_test(
    petoron_ai_goal_policy_ucb_selection_test
    tests/petoron_ai_goal_policy_ucb_selection_test.cpp
    executive
)

petoron_ai_add_cpp_test(
    petoron_ai_goal_policy_safe_ucb_selection_test
    tests/petoron_ai_goal_policy_safe_ucb_selection_test.cpp
    executive
)


add_executable(petoron_ai_multi_objective_utility_test
    tests/petoron_ai_multi_objective_utility_test.cpp
)

target_link_libraries(
    petoron_ai_multi_objective_utility_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_multi_objective_utility_test
    COMMAND $<TARGET_FILE:petoron_ai_multi_objective_utility_test>
)

set_tests_properties(
    petoron_ai_multi_objective_utility_test
    PROPERTIES LABELS "utility;world;multi_objective"
)


add_executable(petoron_ai_decision_arena_test
    tests/petoron_ai_decision_arena_test.cpp
)

target_link_libraries(
    petoron_ai_decision_arena_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_decision_arena_test
    COMMAND $<TARGET_FILE:petoron_ai_decision_arena_test>
)

set_tests_properties(
    petoron_ai_decision_arena_test
    PROPERTIES LABELS "decision;arena;goal"
)


add_executable(petoron_ai_production_safety_test
    tests/petoron_ai_production_safety_test.cpp
)

target_link_libraries(
    petoron_ai_production_safety_test
    PRIVATE
    petoron_ai
)

add_test(
    NAME petoron_ai_production_safety_test
    COMMAND $<TARGET_FILE:petoron_ai_production_safety_test>
)

set_tests_properties(
    petoron_ai_production_safety_test
    PROPERTIES LABELS "production;safety;decision;policy"
)
