/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/strategy/utility_engine.hpp"

#include <vector>

namespace petoron_ai {

struct RankedUtility {
    UtilityAssessment assessment;
    int utility = 0;
};

std::vector<RankedUtility> rank_utilities(
    const std::vector<UtilityAssessment>& assessments
);

}
