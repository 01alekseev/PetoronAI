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
    const fs::path kb0 = (outdir / R"PET(second_cycle_0.pkb)PET");
    const fs::path input_file = (outdir / R"PET(second_cycle.paiin)PET");
    const fs::path s0 = (outdir / R"PET(second_cycle_0.pms)PET");
    const fs::path kb1 = (outdir / R"PET(second_cycle_1.pkb)PET");
    const fs::path c1 = (outdir / R"PET(second_cycle_1.pcycle)PET");
    const fs::path t1 = (outdir / R"PET(second_cycle_1.pkbt)PET");
    const fs::path s1 = (outdir / R"PET(second_cycle_1.pms)PET");
    const fs::path kb2 = (outdir / R"PET(second_cycle_2.pkb)PET");
    const fs::path c2 = (outdir / R"PET(second_cycle_2.pcycle)PET");
    const fs::path t2 = (outdir / R"PET(second_cycle_2.pkbt)PET");
    const fs::path s2 = (outdir / R"PET(second_cycle_2.pms)PET");
    write_text(kb0, R"PET(PKB:1
fact:smoke is visible
fact:smoke can indicate fire
fact:fall can cause injury
fact:injury can be severe
relation:indicates|smoke is visible|smoke can indicate fire
relation:causes|fall can cause injury|injury can be severe
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
observe:smoke is visible
observe:smoke can indicate fire
rule:hypothesis_inference|smoke is visible|smoke can indicate fire|hypothesis:fire exists
rule:risk_inference|hypothesis:fire exists|smoke can indicate fire|fire is dangerous
rule:injury_risk|fall can cause injury|injury can be severe|injury is dangerous
)PET");
    run({((build / R"PET(petoron_ai_init_state)PET")).string(), (kb0).string(), (s0).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (s0).string(), (kb0).string(), (input_file).string(), (kb1).string(), (c1).string(), (t1).string(), (s1).string()});
    run({((build / R"PET(petoron_ai_verify_kb_transition)PET")).string(), (kb0).string(), (input_file).string(), (c1).string(), (kb1).string(), (t1).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (s0).string(), (t1).string(), (s1).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (s1).string(), (kb1).string(), (input_file).string(), (kb2).string(), (c2).string(), (t2).string(), (s2).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (s1).string(), (t2).string(), (s2).string()});
    const std::string text = read_text(kb2);
    const std::vector<std::string> required = {R"PET(fact:strategy:move away effective)PET", R"PET(fact:strategy:stabilize body effective)PET", R"PET(fact:strategy:avoid injury effective)PET", R"PET(fact:active goal:avoid injury)PET", R"PET(fact:injury risk handled)PET"};
    require_all(text, required);
    std::cout << "petoron_ai_second_cycle_learning_test PASS\n";
    return 0;
}
