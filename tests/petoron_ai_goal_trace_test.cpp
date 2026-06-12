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
    const fs::path kb = (outdir / R"PET(goal_trace.pkb)PET");
    const fs::path input_file = (outdir / R"PET(goal_trace.paiin)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is dangerous
fact:fire is dangerous
fact:confidence:storm is dangerous:90
fact:confidence:fire is dangerous:90
fact:strategy_score:avoid storm:5
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
goal_candidate:avoid danger
goal_candidate:protect shelter
observe:storm is dangerous
observe:fire is dangerous
rule:risk_inference|storm is dangerous|fire is dangerous|danger exists
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_trace_goal)PET")).string(), (kb).string(), (input_file).string()});
    const std::vector<std::string> required = {R"PET(candidate: avoid storm)PET", R"PET(base: 80)PET", R"PET(confidence: 90)PET", R"PET(strategy: 50)PET", R"PET(score: 220)PET", R"PET(candidate: avoid fire)PET", R"PET(base: 90)PET", R"PET(score: 180)PET", R"PET(resolved_goal: avoid storm)PET", R"PET(resolved_reason: storm is dangerous)PET", R"PET(resolved_score: 220)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_goal_trace_test PASS\n";
    return 0;
}
