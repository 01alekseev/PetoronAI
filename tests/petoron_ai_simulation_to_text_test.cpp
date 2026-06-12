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
    const fs::path kb = (outdir / R"PET(simulation_to_text.pkb)PET");
    const fs::path input_file = (outdir / R"PET(simulation_to_text.paiin)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is dangerous
fact:confidence:storm is dangerous:90
fact:strategy_score:avoid storm:5
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
goal_candidate:avoid danger
goal_candidate:protect shelter
observe:storm is dangerous
rule:risk_inference|storm is dangerous|storm is dangerous|storm is dangerous
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_simulation_to_text)PET")).string(), (kb).string(), (input_file).string()});
    const std::vector<std::string> required = {R"PET(Goal: avoid storm)PET", R"PET(Selected action: find shelter)PET", R"PET(Expected future: safe shelter)PET", R"PET(Risk: 10)PET", R"PET(Rejected action: stay outside)PET", R"PET(Rejected future: storm exposure)PET", R"PET(Rejected risk: 90)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_simulation_to_text_test PASS\n";
    return 0;
}
