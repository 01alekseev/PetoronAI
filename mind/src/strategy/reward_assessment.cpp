/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/reward_assessment.hpp"

namespace petoron_ai {

int effective_reward_score(
    const RewardAssessment& assessment
) {
    return
        assessment.score +
        assessment.reward -
        assessment.risk;
}

}
