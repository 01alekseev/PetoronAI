/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/world/world_model.hpp"

namespace petoron_ai {

std::vector<WorldRelation> infer_world_relations(
    const WorldModel& model
);

}
