/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai_test_common.hpp"

int main() {
    namespace fs = std::filesystem;
    using namespace petoron_ai_test;
    const fs::path root = fs::current_path();
    const fs::path build = root / "build";
    const fs::path outdir = root / "var" / "tests";
    fs::create_directories(outdir);
    const std::string out = output({((build / R"PET(petoron_ai_plan_goal)PET")).string(), R"PET(avoid storm)PET"});
    const std::vector<std::string> required = {R"PET(goal: avoid storm)PET", R"PET(step 1: search for shelter)PET", R"PET(step 2: secure shelter entrance)PET", R"PET(step 3: stay inside shelter)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_plan_goal_test PASS\n";
    return 0;
}
