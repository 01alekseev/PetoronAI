/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include "petoron_ai/experience/experience_record.hpp"

#include <string>

namespace petoron_ai {

bool read_experience_file(
    const std::string& path,
    ExperienceRecord& record
);

}
