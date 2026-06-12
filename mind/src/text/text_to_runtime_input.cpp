/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/text/text_to_runtime_input.hpp"

#include <algorithm>
#include <cctype>

namespace petoron_ai {

static std::string lower_copy(
    std::string value
) {
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

static ReasoningRule make_rule(
    const std::string& name,
    const std::string& left,
    const std::string& right,
    const std::string& conclusion
) {
    ReasoningRule rule;
    rule.name = name;
    rule.left_payload = left;
    rule.right_payload = right;
    rule.conclusion_payload = conclusion;
    return rule;
}

RuntimeInput text_to_runtime_input(
    const std::string& raw_text
) {
    const std::string text =
        lower_copy(raw_text);

    RuntimeInput input;
    input.goal.name = "avoid danger";

    if (
        contains(text, "dark cloud") ||
        contains(text, "dark clouds")
    ) {
        input.observations.push_back(
            "dark clouds visible"
        );

        input.observations.push_back(
            "dark clouds can indicate storm"
        );

        input.rules.push_back(
            make_rule(
                "hypothesis_inference",
                "dark clouds visible",
                "dark clouds can indicate storm",
                "hypothesis:storm exists"
            )
        );
    }

    if (contains(text, "storm")) {
        input.observations.push_back(
            "storm can damage shelter"
        );

        input.rules.push_back(
            make_rule(
                "risk_inference",
                "hypothesis:storm exists",
                "storm can damage shelter",
                "storm is dangerous"
            )
        );
    }

    if (contains(text, "smoke")) {
        input.observations.push_back(
            "smoke is visible"
        );

        input.observations.push_back(
            "smoke can indicate fire"
        );

        input.rules.push_back(
            make_rule(
                "hypothesis_inference",
                "smoke is visible",
                "smoke can indicate fire",
                "hypothesis:fire exists"
            )
        );

        input.rules.push_back(
            make_rule(
                "risk_inference",
                "hypothesis:fire exists",
                "smoke can indicate fire",
                "fire is dangerous"
            )
        );
    }

    return input;
}

}
