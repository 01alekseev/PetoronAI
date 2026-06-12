/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/future_simulator.hpp"
#include "petoron_ai/goal_resolver.hpp"
#include "petoron_ai/runtime_input.hpp"
#include "petoron_ai/knowledge/knowledge_file.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

static std::string lower_copy(std::string value) {
    std::transform(
        value.begin(),
        value.end(),
        value.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        }
    );

    return value;
}

static bool contains(
    const std::string& text,
    const std::string& needle
) {
    return text.find(needle) != std::string::npos;
}

static bool write_input(
    const std::string& text_raw,
    const std::string& path
) {
    const std::string text = lower_copy(text_raw);
    std::ofstream out(path, std::ios::binary);

    if (!out) {
        return false;
    }

    out << "PAIIN:1\n";
    out << "goal:auto\n";
    out << "goal_candidate:avoid danger\n";

    if (contains(text, "shelter")) {
        out << "goal_candidate:protect shelter\n";
    }

    if (contains(text, "dark cloud") || contains(text, "dark clouds")) {
        out << "observe:dark clouds visible\n";
        out << "observe:dark clouds can indicate storm\n";
        out << "rule:hypothesis_inference|dark clouds visible|dark clouds can indicate storm|hypothesis:storm exists\n";
    }

    if (contains(text, "storm")) {
        out << "observe:storm can damage shelter\n";
        out << "rule:risk_inference|hypothesis:storm exists|storm can damage shelter|storm is dangerous\n";
    }

    if (contains(text, "smoke")) {
        out << "observe:smoke is visible\n";
        out << "observe:smoke can indicate fire\n";
        out << "rule:hypothesis_inference|smoke is visible|smoke can indicate fire|hypothesis:fire exists\n";
        out << "rule:risk_inference|hypothesis:fire exists|smoke can indicate fire|fire is dangerous\n";
    }

    return true;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: petoron_ai_ask <world.pkb> <text>\n";
        return 1;
    }

    const std::string input_path = "/tmp/petoron_ai_ask_runtime.paiin";

    if (!write_input(argv[2], input_path)) {
        std::cerr << "input write failed\n";
        return 2;
    }

    petoron_ai::KnowledgeStore kb;
    petoron_ai::RuntimeInput input;

    if (!petoron_ai::read_knowledge_file(argv[1], kb)) {
        std::cerr << "kb read failed\n";
        return 3;
    }

    if (!petoron_ai::read_runtime_input(input_path, input)) {
        std::cerr << "input read failed\n";
        return 4;
    }

    const auto resolution =
        petoron_ai::resolve_goal_trace(kb, input);

    const auto outcomes =
        petoron_ai::simulate_goal(resolution);

    std::cout << "Goal: " << resolution.resolved_goal << "\n";

    const petoron_ai::FutureOutcome* selected = nullptr;

    for (const auto& outcome : outcomes) {
        if (selected == nullptr || outcome.risk_score < selected->risk_score) {
            selected = &outcome;
        }
    }

    if (selected == nullptr) {
        std::cout << "No simulated action available\n";
        return 0;
    }

    std::cout << "Selected action: " << selected->action << "\n";
    std::cout << "Expected future: " << selected->future_state << "\n";
    std::cout << "Risk: " << selected->risk_score << "\n";

    return 0;
}
