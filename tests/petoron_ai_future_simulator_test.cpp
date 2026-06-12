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
    const fs::path kb = (outdir / R"PET(future_simulator.pkb)PET");
    const fs::path input_file = (outdir / R"PET(future_simulator.paiin)PET");
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
    const std::string out = output({((build / R"PET(petoron_ai_simulate_goal)PET")).string(), (kb).string(), (input_file).string()});
    const std::vector<std::string> required = {R"PET(goal: avoid storm)PET", R"PET(candidate_action: find shelter)PET", R"PET(future_state: safe shelter)PET", R"PET(risk_score: 10)PET", R"PET(candidate_action: stay outside)PET", R"PET(future_state: storm exposure)PET", R"PET(risk_score: 90)PET", R"PET(selected_action: find shelter)PET", R"PET(selected_future: safe shelter)PET", R"PET(selected_risk: 10)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_future_simulator_test PASS\n";
    return 0;
}
