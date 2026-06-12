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
    const fs::path old_kb = (outdir / R"PET(step_test_old.pkb)PET");
    const fs::path old_state = (outdir / R"PET(step_test_old.pms)PET");
    const fs::path new_kb = (outdir / R"PET(step_test_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(step_test.pcycle)PET");
    const fs::path transition = (outdir / R"PET(step_test.pkbt)PET");
    const fs::path new_state = (outdir / R"PET(step_test_new.pms)PET");
    const fs::path input_file = (root / R"PET(petoron_ai_fire.paiin)PET");
    write_text(old_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");
    run({((build / R"PET(petoron_ai_init_state)PET")).string(), (old_kb).string(), (old_state).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (old_state).string(), (old_kb).string(), (input_file).string(), (new_kb).string(), (cycle).string(), (transition).string(), (new_state).string()});
    run({((build / R"PET(petoron_ai_verify_kb_transition)PET")).string(), (old_kb).string(), (input_file).string(), (cycle).string(), (new_kb).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (old_state).string(), (transition).string(), (new_state).string()});
    std::cout << "petoron_ai_step_test PASS\n";
    return 0;
}
