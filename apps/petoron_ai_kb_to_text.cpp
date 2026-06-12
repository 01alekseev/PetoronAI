/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static bool starts_with(
    const std::string& value,
    const std::string& prefix
) {
    return value.rfind(prefix, 0) == 0;
}

static bool ends_with(
    const std::string& value,
    const std::string& suffix
) {
    if (value.size() < suffix.size()) {
        return false;
    }

    return value.compare(
        value.size() - suffix.size(),
        suffix.size(),
        suffix
    ) == 0;
}

static std::string strip_prefix(
    const std::string& value,
    const std::string& prefix
) {
    return value.substr(prefix.size());
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: petoron_ai_kb_to_text <input.pkb>\n";
        return 1;
    }

    std::ifstream in(argv[1], std::ios::binary);

    if (!in) {
        std::cerr << "read failed\n";
        return 2;
    }

    std::vector<std::string> facts;
    std::string line;

    while (std::getline(in, line)) {
        if (starts_with(line, "fact:")) {
            facts.push_back(strip_prefix(line, "fact:"));
        }
    }

    for (const auto& fact : facts) {
        if (starts_with(fact, "hypothesis:")) {
            std::cout << "Hypothesis: "
                      << strip_prefix(fact, "hypothesis:")
                      << "\n";
        }
    }

    for (const auto& fact : facts) {
        if (
            ends_with(fact, " is dangerous") &&
            !starts_with(fact, "explain:")
        ) {
            std::cout << "Risk: " << fact << "\n";
        }
    }

    for (const auto& fact : facts) {
        if (
            starts_with(fact, "confidence:") &&
            fact.find(" is dangerous:") != std::string::npos
        ) {
            std::cout << "Confidence: "
                      << strip_prefix(fact, "confidence:")
                      << "\n";
        }
    }

    for (const auto& fact : facts) {
        if (
            starts_with(fact, "active goal:") ||
            ends_with(fact, " completed")
        ) {
            std::cout << "Action: " << fact << "\n";
        }
    }

    for (const auto& fact : facts) {
        if (starts_with(fact, "explain:")) {
            std::cout << "Explanation: "
                      << strip_prefix(fact, "explain:")
                      << "\n";
        }
    }

    for (const auto& fact : facts) {
        if (starts_with(fact, "strategy:")) {
            std::cout << "Learned: "
                      << strip_prefix(fact, "strategy:")
                      << "\n";
        }
    }

    return 0;
}
