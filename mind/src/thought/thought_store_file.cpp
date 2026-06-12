/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_store_file.hpp"

#include <charconv>
#include <fstream>
#include <string>

namespace petoron_ai {

static bool starts_with(
    const std::string& value,
    const std::string& prefix
) {
    return value.rfind(prefix, 0) == 0;
}

bool write_thought_store_file(
    const std::string& path,
    const ThoughtStore& store
) {
    std::ofstream out(path, std::ios::binary);

    if (!out) {
        return false;
    }

    out << "PTS:1\n";

    for (const auto& item : store.thoughts) {
        out << "thought:" << item.thought << "\n";
        out << "reason:" << item.reason << "\n";
        out << "source_goal:" << item.source_goal << "\n";
        out << "confidence:" << item.confidence << "\n";
        out << "end\n";
    }

    return true;
}

bool read_thought_store_file(
    const std::string& path,
    ThoughtStore& store
) {
    std::ifstream in(path, std::ios::binary);

    if (!in) {
        return false;
    }

    std::string line;

    if (!std::getline(in, line)) {
        return false;
    }

    if (line != "PTS:1") {
        return false;
    }

    store.thoughts.clear();

    std::string thought;
    std::string reason;
    std::string source_goal;
    int confidence = 0;

    while (std::getline(in, line)) {
        if (starts_with(line, "thought:")) {
            thought = line.substr(8);
            continue;
        }

        if (starts_with(line, "reason:")) {
            reason = line.substr(7);
            continue;
        }

        if (starts_with(line, "source_goal:")) {
            source_goal = line.substr(12);
            continue;
        }

        if (starts_with(line, "confidence:")) {
            const auto value = line.substr(11);
            const auto result =
                std::from_chars(
                    value.data(),
                    value.data() + value.size(),
                    confidence
                );

            if (
                result.ec != std::errc{} ||
                result.ptr != value.data() + value.size()
            ) {
                return false;
            }

            continue;
        }

        if (line == "end") {
            const auto artifact =
                make_thought_artifact(
                    thought,
                    reason,
                    source_goal,
                    confidence
                );

            add_thought(store, artifact);

            thought.clear();
            reason.clear();
            source_goal.clear();
            confidence = 0;
            continue;
        }

        return false;
    }

    return true;
}

}
