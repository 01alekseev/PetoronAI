/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/goal_resolver.hpp"
#include "petoron_ai/experience/experience_statistics.hpp"

#include <charconv>

namespace petoron_ai {

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

static int base_priority(
    const std::string& target
) {
    if (target == "injury") return 100;
    if (target == "fire") return 90;
    if (target == "storm") return 80;
    if (target == "thirst") return 70;
    if (target == "danger") return 60;

    return 10;
}

static int parse_int(
    const std::string& value
) {
    int out = 0;

    const auto* begin = value.data();
    const auto* end = value.data() + value.size();
    const auto result = std::from_chars(begin, end, out);

    if (result.ec != std::errc{} || result.ptr != end) {
        return 0;
    }

    return out;
}

static int confidence_bonus(
    const KnowledgeStore& kb,
    const std::string& danger_fact
) {
    const std::string prefix = "confidence:" + danger_fact + ":";

    for (const auto& fact : kb.facts()) {
        if (starts_with(fact, prefix)) {
            return parse_int(fact.substr(prefix.size()));
        }
    }

    return 0;
}


static int experience_bonus(
    const KnowledgeStore& kb,
    const std::string& goal
) {
    const auto stats =
        experience_statistics(
            kb,
            goal
        );

    if (stats.experience_count == 0) {
        return 0;
    }

    return stats.success_rate + (stats.average_reward / 10);
}

static int strategy_bonus(
    const KnowledgeStore& kb,
    const std::string& target
) {
    const std::string prefix = "strategy_score:avoid " + target + ":";

    for (const auto& fact : kb.facts()) {
        if (starts_with(fact, prefix)) {
            return parse_int(fact.substr(prefix.size())) * 10;
        }
    }

    return 0;
}

GoalResolution resolve_goal_trace(
    const KnowledgeStore& kb,
    const RuntimeInput& input
) {
    GoalResolution resolution;
    const std::string suffix = " is dangerous";

    for (const auto& fact : kb.facts()) {
        if (!ends_with(fact, suffix)) {
            continue;
        }

        GoalResolutionCandidate candidate;
        candidate.target = fact.substr(0, fact.size() - suffix.size());
        candidate.goal = "avoid " + candidate.target;
        candidate.reason = fact;
        candidate.base = base_priority(candidate.target);
        candidate.confidence = confidence_bonus(kb, fact);
        candidate.strategy = strategy_bonus(kb, candidate.target);
        candidate.experience = experience_bonus(kb, candidate.goal);
        candidate.score =
            candidate.base +
            candidate.confidence +
            candidate.strategy +
            candidate.experience;

        resolution.candidates.push_back(candidate);

        if (
            resolution.resolved_goal.empty() ||
            candidate.score > resolution.resolved_score
        ) {
            resolution.resolved_goal = candidate.goal;
            resolution.resolved_reason = candidate.reason;
            resolution.resolved_score = candidate.score;
        }
    }

    if (resolution.resolved_goal.empty() && !input.goal_candidates.empty()) {
        resolution.resolved_goal = input.goal_candidates.front().name;
        resolution.resolved_reason = "fallback goal candidate";
        resolution.resolved_score = 0;
    }

    if (resolution.resolved_goal.empty()) {
        resolution.resolved_goal = input.goal.name;
        resolution.resolved_reason = "fallback input goal";
        resolution.resolved_score = 0;
    }

    return resolution;
}

std::string resolve_goal(
    const KnowledgeStore& kb,
    const RuntimeInput& input
) {
    return resolve_goal_trace(kb, input).resolved_goal;
}

}
