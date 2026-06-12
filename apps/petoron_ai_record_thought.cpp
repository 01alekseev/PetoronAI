/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "common/hex.hpp"
#include "petoron_ai/thought/thought_artifact.hpp"

#include <charconv>
#include <iostream>
#include <string>

static bool parse_int(
    const char* text,
    int& out
) {
    const std::string value = text;

    const auto result =
        std::from_chars(
            value.data(),
            value.data() + value.size(),
            out
        );

    return result.ec == std::errc{} &&
        result.ptr == value.data() + value.size();
}

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "usage: petoron_ai_record_thought <thought> <reason> <source_goal> <confidence>\n";
        return 1;
    }

    int confidence = 0;

    if (!parse_int(argv[4], confidence)) {
        return 2;
    }

    const auto artifact =
        petoron_ai::make_thought_artifact(
            argv[1],
            argv[2],
            argv[3],
            confidence
        );

    std::cout << "thought: " << artifact.thought << "\n";
    std::cout << "reason: " << artifact.reason << "\n";
    std::cout << "source_goal: " << artifact.source_goal << "\n";
    std::cout << "confidence: " << artifact.confidence << "\n";

    std::cout << "thought_id: ";
    petoron_ai_app::print_digest(artifact.id);
    std::cout << "\n";

    return 0;
}
