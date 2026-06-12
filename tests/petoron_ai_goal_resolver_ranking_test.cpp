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
    const fs::path kb = (outdir / R"PET(goal_resolver_ranking.pkb)PET");
    const fs::path input_file = (outdir / R"PET(goal_resolver_ranking.paiin)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is dangerous
fact:fire is dangerous
fact:confidence:storm is dangerous:90
fact:confidence:fire is dangerous:90
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
goal_candidate:avoid danger
goal_candidate:protect shelter
observe:storm is dangerous
observe:fire is dangerous
rule:risk_inference|storm is dangerous|fire is dangerous|danger exists
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_resolve_goal)PET")).string(), (kb).string(), (input_file).string()});
    require_contains(out, R"PET(resolved_goal: avoid fire)PET");
    std::cout << "petoron_ai_goal_resolver_ranking_test PASS\n";
    return 0;
}
