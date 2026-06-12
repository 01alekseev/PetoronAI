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
    const fs::path kb = (outdir / R"PET(goal_resolver.pkb)PET");
    const fs::path input_file = (outdir / R"PET(goal_resolver.paiin)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is dangerous
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
goal_candidate:avoid danger
goal_candidate:protect shelter
observe:storm can damage shelter
rule:risk_inference|storm is forming|storm can damage shelter|storm is dangerous
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_resolve_goal)PET")).string(), (kb).string(), (input_file).string()});
    require_contains(out, R"PET(resolved_goal: avoid storm)PET");
    std::cout << "petoron_ai_goal_resolver_test PASS\n";
    return 0;
}
