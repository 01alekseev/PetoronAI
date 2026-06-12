/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

namespace petoron_ai {

struct RiskAssessment {
    int score = 0;
    int risk = 0;
};

int effective_score(
    const RiskAssessment& assessment
);

}
