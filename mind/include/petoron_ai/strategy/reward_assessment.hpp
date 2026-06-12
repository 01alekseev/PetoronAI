/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

namespace petoron_ai {

struct RewardAssessment {
    int score = 0;
    int reward = 0;
    int risk = 0;
};

int effective_reward_score(
    const RewardAssessment& assessment
);

}
