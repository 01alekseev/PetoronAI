/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/strategy/utility_ranking.hpp"

#include <algorithm>

namespace petoron_ai {

std::vector<RankedUtility> rank_utilities(
    const std::vector<UtilityAssessment>& assessments
) {
    std::vector<RankedUtility> ranked;

    for (const auto& assessment : assessments) {
        ranked.push_back(
            {
                assessment,
                compute_utility(assessment)
            }
        );
    }

    std::sort(
        ranked.begin(),
        ranked.end(),
        [](const RankedUtility& a,
           const RankedUtility& b)
        {
            return a.utility > b.utility;
        }
    );

    return ranked;
}

}
