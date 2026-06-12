/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime_input.hpp"

#include <fstream>
#include <sstream>

namespace petoron_ai {

static bool starts_with(
    const std::string& text,
    const std::string& prefix
) {
    return text.rfind(prefix, 0) == 0;
}

static bool empty_value(
    const std::string& value
) {
    return value.empty();
}

bool read_runtime_input(
    const std::string& path,
    RuntimeInput& input
) {
    input = RuntimeInput{};

    std::ifstream in(path);

    if (!in) {
        return false;
    }

    std::string line;

    if (!std::getline(in, line)) {
        return false;
    }

    if (line != "PAIIN:1") {
        return false;
    }

    while (std::getline(in, line)) {
        if (line.empty()) {
            return false;
        }

        if (starts_with(line, "goal:")) {
            if (!input.goal.name.empty()) {
                return false;
            }

            input.goal.name = line.substr(5);
            if (empty_value(input.goal.name)) {
                return false;
            }

            continue;
        }

        if (starts_with(line, "goal_candidate:")) {
            Goal candidate;
            candidate.name = line.substr(15);

            if (empty_value(candidate.name)) {
                return false;
            }

            input.goal_candidates.push_back(candidate);
            continue;
        }

        if (starts_with(line, "observe:")) {
            const auto value = line.substr(8);
            if (empty_value(value)) {
                return false;
            }

            input.observations.push_back(value);
            continue;
        }

        if (starts_with(line, "rule:")) {
            std::string body = line.substr(5);
            if (body.empty()) {
                return false;
            }

            std::stringstream ss(body);

            std::string name;
            std::string left;
            std::string right;
            std::string conclusion;
            std::string extra;

            if (!std::getline(ss, name, '|')) {
                return false;
            }

            if (!std::getline(ss, left, '|')) {
                return false;
            }

            if (!std::getline(ss, right, '|')) {
                return false;
            }

            if (!std::getline(ss, conclusion, '|')) {
                return false;
            }

            if (std::getline(ss, extra, '|')) {
                return false;
            }

            if (
                empty_value(name) ||
                empty_value(left) ||
                empty_value(right) ||
                empty_value(conclusion)
            ) {
                return false;
            }

            ReasoningRule rule;
            rule.name = name;
            rule.left_payload = left;
            rule.right_payload = right;
            rule.conclusion_payload = conclusion;

            input.rules.push_back(rule);
            continue;
        }

        return false;
    }

    if (input.goal.name.empty()) {
        return false;
    }

    if (input.observations.empty()) {
        return false;
    }

    return !input.rules.empty();
}

}
