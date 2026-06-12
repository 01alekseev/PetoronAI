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
    const fs::path kb = (outdir / R"PET(goal_resolver_fallback.pkb)PET");
    const fs::path input_file = (outdir / R"PET(goal_resolver_fallback.paiin)PET");
    write_text(kb, R"PET(PKB:1
fact:shelter exists
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
goal_candidate:protect shelter
goal_candidate:avoid danger
observe:shelter exists
rule:identity|shelter exists|shelter exists|shelter exists
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_trace_goal)PET")).string(), (kb).string(), (input_file).string()});
    const std::vector<std::string> required = {R"PET(resolved_goal: protect shelter)PET", R"PET(resolved_reason: fallback goal candidate)PET", R"PET(resolved_score: 0)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_goal_resolver_fallback_test PASS\n";
    return 0;
}
