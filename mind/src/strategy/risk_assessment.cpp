/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/risk_assessment.hpp"

namespace petoron_ai {

int effective_score(
    const RiskAssessment& assessment
) {
    return assessment.score - assessment.risk;
}

}
