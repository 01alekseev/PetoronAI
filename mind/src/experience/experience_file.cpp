/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/experience/experience_file.hpp"

#include <fstream>

namespace petoron_ai {

static bool starts_with(
    const std::string& value,
    const std::string& prefix
) {
    return value.rfind(prefix, 0) == 0;
}

static bool parse_int(
    const std::string& value,
    int& out
) {
    if (value.empty()) {
        return false;
    }

    int sign = 1;
    std::size_t index = 0;

    if (value[0] == '-') {
        sign = -1;
        index = 1;
    }

    if (index == value.size()) {
        return false;
    }

    int result = 0;

    for (; index < value.size(); ++index) {
        const char c = value[index];

        if (c < '0' || c > '9') {
            return false;
        }

        result = result * 10 + (c - '0');
    }

    out = result * sign;
    return true;
}

bool read_experience_file(
    const std::string& path,
    ExperienceRecord& record
) {
    record = ExperienceRecord{};

    std::ifstream in(path);

    if (!in) {
        return false;
    }

    std::string line;

    if (!std::getline(in, line) || line != "PEXP:1") {
        return false;
    }

    while (std::getline(in, line)) {
        if (starts_with(line, "goal:")) {
            record.goal = line.substr(5);
            continue;
        }

        if (starts_with(line, "action:")) {
            record.action = line.substr(7);
            continue;
        }

        if (starts_with(line, "predicted_risk:")) {
            if (!parse_int(line.substr(15), record.predicted_risk)) {
                return false;
            }

            continue;
        }

        if (starts_with(line, "actual_result:")) {
            record.actual_result = line.substr(14);
            continue;
        }

        if (starts_with(line, "reward:")) {
            if (!parse_int(line.substr(7), record.reward)) {
                return false;
            }

            continue;
        }

        return false;
    }

    return
        !record.goal.empty() &&
        !record.action.empty() &&
        !record.actual_result.empty();
}

}
