/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning/counterfactual_reasoning.hpp"

namespace petoron_ai {

CounterfactualComparison compare_futures(
    const std::string& actual_action,
    int actual_risk,
    const std::string& alternative_action,
    int alternative_risk
) {
    CounterfactualComparison result;

    result.actual_action = actual_action;
    result.actual_risk = actual_risk;

    result.alternative_action = alternative_action;
    result.alternative_risk = alternative_risk;

    result.preferred_action =
        actual_risk <= alternative_risk
            ? actual_action
            : alternative_action;

    return result;
}

}
