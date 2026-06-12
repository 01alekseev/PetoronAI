/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning/hypothesis_generator.hpp"

namespace petoron_ai {

std::vector<std::string> generate_hypotheses(
    const std::vector<std::string>& context
) {
    std::vector<std::string> hypotheses;

    bool storm = false;
    bool shelter = false;

    for (const auto& fact : context) {
        if (fact.find("storm") != std::string::npos) {
            storm = true;
        }

        if (fact.find("shelter") != std::string::npos) {
            shelter = true;
        }
    }

    if (storm && shelter) {
        hypotheses.push_back("find shelter");
    }

    if (storm) {
        hypotheses.push_back("leave area");
        hypotheses.push_back("wait for storm to pass");
    }

    if (hypotheses.empty()) {
        hypotheses.push_back("gather more information");
    }

    return hypotheses;
}

}
