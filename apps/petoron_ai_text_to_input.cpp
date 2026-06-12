/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

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

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: petoron_ai_text_to_input <text> <out.paiin>\n";
        return 1;
    }

    const std::string text = lower_copy(argv[1]);
    std::ofstream out(argv[2], std::ios::binary);

    if (!out) {
        std::cerr << "write failed\n";
        return 2;
    }

    out << "PAIIN:1\n";
    out << "goal:avoid danger\n";

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

    return 0;
}
