/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

namespace petoron_ai {

struct UtilityAssessment {
    int base_score = 0;

    int reward = 0;
    int risk = 0;
    int resource_cost = 0;
    int experience_weight = 0;

    int survival_value = 0;
    int safety_value = 0;
    int knowledge_value = 0;
    int resource_value = 0;
};

int compute_utility(
    const UtilityAssessment& assessment
);

}
