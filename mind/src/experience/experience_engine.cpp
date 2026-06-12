/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/experience/experience_engine.hpp"

#include <algorithm>
#include <string>

namespace petoron_ai {

static bool starts_with(
    const std::string& value,
    const std::string& prefix
) {
    return value.rfind(prefix, 0) == 0;
}

static int parse_score(
    const std::string& value
) {
    int result = 0;

    for (const char c : value) {
        if (c < '0' || c > '9') {
            return 0;
        }

        result = result * 10 + (c - '0');
    }

    return result;
}

static int score_delta(
    const ExperienceRecord& record
) {
    if (record.reward > 0 || record.actual_result == "success") {
        return 1;
    }

    if (record.reward < 0 || record.actual_result == "failure") {
        return -1;
    }

    return 0;
}

static int find_max_value(
    const KnowledgeStore& kb,
    const std::string& prefix
) {
    int best = 0;

    for (const auto& fact : kb.facts()) {
        if (starts_with(fact, prefix)) {
            best = std::max(
                best,
                parse_score(fact.substr(prefix.size()))
            );
        }
    }

    return best;
}

static void copy_without_experience_keys(
    KnowledgeStore& target,
    const KnowledgeStore& source,
    const std::string& goal
) {
    const std::string score_prefix =
        "strategy_score:" + goal + ":";

    const std::string experience_prefix =
        "experience_count:" + goal + ":";

    const std::string success_prefix =
        "success_count:" + goal + ":";

    const std::string failure_prefix =
        "failure_count:" + goal + ":";

    const std::string reward_prefix =
        "average_reward:" + goal + ":";

    const auto facts = source.facts();

    for (const auto& fact : facts) {
        if (
            starts_with(fact, score_prefix) ||
            starts_with(fact, experience_prefix) ||
            starts_with(fact, success_prefix) ||
            starts_with(fact, failure_prefix) ||
            starts_with(fact, reward_prefix)
        ) {
            continue;
        }

        target.add_fact(fact);
    }

    for (const auto& from : facts) {
        for (const auto& relation : source.relations_from(from)) {
            target.add_relation(relation);
        }
    }
}

void apply_experience(
    KnowledgeStore& kb,
    const ExperienceRecord& record
) {
    const auto delta = score_delta(record);

    if (delta == 0) {
        return;
    }

    const std::string score_prefix =
        "strategy_score:" + record.goal + ":";

    const std::string experience_prefix =
        "experience_count:" + record.goal + ":";

    const std::string success_prefix =
        "success_count:" + record.goal + ":";

    const std::string failure_prefix =
        "failure_count:" + record.goal + ":";

    const std::string reward_prefix =
        "average_reward:" + record.goal + ":";

    const auto current_score =
        find_max_value(kb, score_prefix);

    const auto current_experience =
        find_max_value(kb, experience_prefix);

    const auto current_success =
        find_max_value(kb, success_prefix);

    const auto current_failure =
        find_max_value(kb, failure_prefix);

    const auto current_average_reward =
        find_max_value(kb, reward_prefix);

    int next_score = current_score + delta;

    if (next_score < 0) {
        next_score = 0;
    }

    const int next_experience =
        current_experience + 1;

    int next_success = current_success;
    int next_failure = current_failure;

    if (record.actual_result == "success" || record.reward > 0) {
        ++next_success;
    } else if (record.actual_result == "failure" || record.reward < 0) {
        ++next_failure;
    }

    const int next_average_reward =
        (
            current_average_reward * current_experience +
            record.reward
        ) / next_experience;

    KnowledgeStore next;

    copy_without_experience_keys(
        next,
        kb,
        record.goal
    );

    next.add_fact(
        score_prefix + std::to_string(next_score)
    );

    next.add_fact(
        experience_prefix + std::to_string(next_experience)
    );

    next.add_fact(
        success_prefix + std::to_string(next_success)
    );

    next.add_fact(
        failure_prefix + std::to_string(next_failure)
    );

    next.add_fact(
        reward_prefix + std::to_string(next_average_reward)
    );

    kb = next;
}

}
