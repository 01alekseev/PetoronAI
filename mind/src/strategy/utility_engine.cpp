/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/utility_engine.hpp"

namespace petoron_ai {

int compute_utility(
    const UtilityAssessment& assessment
) {
    return
        assessment.base_score +
        assessment.reward -
        assessment.risk -
        assessment.resource_cost +
        assessment.experience_weight +
        assessment.survival_value +
        assessment.safety_value +
        assessment.knowledge_value +
        assessment.resource_value;
}

}
