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
    const fs::path kb = (outdir / R"PET(goal_resolver_experience_weight.pkb)PET");
    const fs::path input_file = (outdir / R"PET(goal_resolver_experience_weight.paiin)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is dangerous
fact:fire is dangerous
fact:confidence:storm is dangerous:20
fact:confidence:fire is dangerous:90
fact:experience_count:avoid storm:10
fact:success_count:avoid storm:10
fact:failure_count:avoid storm:0
fact:average_reward:avoid storm:100
fact:experience_count:avoid fire:10
fact:success_count:avoid fire:0
fact:failure_count:avoid fire:10
fact:average_reward:avoid fire:0
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
goal_candidate:avoid danger
observe:storm is dangerous
observe:fire is dangerous
rule:risk_inference|storm is dangerous|fire is dangerous|danger exists
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_trace_goal)PET")).string(), (kb).string(), (input_file).string()});
    const std::vector<std::string> required = {R"PET(candidate: avoid storm)PET", R"PET(experience: 110)PET", R"PET(score: 210)PET", R"PET(candidate: avoid fire)PET", R"PET(experience: 0)PET", R"PET(score: 180)PET", R"PET(resolved_goal: avoid storm)PET", R"PET(resolved_score: 210)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_goal_resolver_experience_weight_test PASS\n";
    return 0;
}
