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
    const fs::path kb = (outdir / R"PET(generic_risk.pkb)PET");
    const fs::path input_file = (outdir / R"PET(generic_risk.paiin)PET");
    const fs::path old_state = (outdir / R"PET(generic_risk_old.pms)PET");
    const fs::path new_kb = (outdir / R"PET(generic_risk_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(generic_risk.pcycle)PET");
    const fs::path transition = (outdir / R"PET(generic_risk.pkbt)PET");
    const fs::path new_state = (outdir / R"PET(generic_risk_new.pms)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is forming
fact:storm can damage shelter
relation:causes|storm is forming|storm can damage shelter
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:avoid danger
observe:storm is forming
observe:storm can damage shelter
rule:risk_inference|storm is forming|storm can damage shelter|storm is dangerous
)PET");
    run({((build / R"PET(petoron_ai_init_state)PET")).string(), (kb).string(), (old_state).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (old_state).string(), (kb).string(), (input_file).string(), (new_kb).string(), (cycle).string(), (transition).string(), (new_state).string()});
    const std::string text = read_text(new_kb);
    const std::vector<std::string> required = {R"PET(fact:storm is dangerous)PET", R"PET(fact:avoid storm completed)PET", R"PET(fact:plan succeeded)PET", R"PET(fact:active goal:avoid storm)PET", R"PET(fact:confidence:storm is dangerous:90)PET", R"PET(fact:strategy:avoid storm effective)PET", R"PET(fact:strategy_score:avoid storm:1)PET"};
    require_all(text, required);
    run({((build / R"PET(petoron_ai_verify_kb_transition)PET")).string(), (kb).string(), (input_file).string(), (cycle).string(), (new_kb).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (old_state).string(), (transition).string(), (new_state).string()});
    std::cout << "petoron_ai_generic_risk_test PASS\n";
    return 0;
}
