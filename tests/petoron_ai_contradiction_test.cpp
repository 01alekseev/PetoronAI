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
    const fs::path kb = (outdir / R"PET(contradiction.pkb)PET");
    const fs::path input_file = (outdir / R"PET(contradiction.paiin)PET");
    const fs::path old_state = (outdir / R"PET(contradiction_old.pms)PET");
    const fs::path new_kb = (outdir / R"PET(contradiction_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(contradiction.pcycle)PET");
    const fs::path transition = (outdir / R"PET(contradiction.pkbt)PET");
    const fs::path new_state = (outdir / R"PET(contradiction_new.pms)PET");
    write_text(kb, R"PET(PKB:1
fact:fire exists
fact:no fire exists
relation:conflicts|fire exists|no fire exists
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:auto
observe:fire exists
observe:no fire exists
rule:contradiction_inference|fire exists|no fire exists|contradiction:fire exists
rule:risk_inference|contradiction:fire exists|fire exists|knowledge is unstable
)PET");
    run({((build / R"PET(petoron_ai_init_state)PET")).string(), (kb).string(), (old_state).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (old_state).string(), (kb).string(), (input_file).string(), (new_kb).string(), (cycle).string(), (transition).string(), (new_state).string()});
    const std::string text = read_text(new_kb);
    const std::vector<std::string> required = {R"PET(fact:contradiction:fire exists)PET", R"PET(fact:knowledge is unstable)PET", R"PET(fact:confidence:knowledge is unstable:95)PET"};
    require_all(text, required);
    run({((build / R"PET(petoron_ai_verify_kb_transition)PET")).string(), (kb).string(), (input_file).string(), (cycle).string(), (new_kb).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (old_state).string(), (transition).string(), (new_state).string()});
    std::cout << "petoron_ai_contradiction_test PASS\n";
    return 0;
}
