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
    const fs::path kb = (outdir / R"PET(recursive_reasoning.pkb)PET");
    const fs::path input_file = (outdir / R"PET(recursive_reasoning.paiin)PET");
    const fs::path old_state = (outdir / R"PET(recursive_reasoning_old.pms)PET");
    const fs::path new_kb = (outdir / R"PET(recursive_reasoning_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(recursive_reasoning.pcycle)PET");
    const fs::path transition = (outdir / R"PET(recursive_reasoning.pkbt)PET");
    const fs::path new_state = (outdir / R"PET(recursive_reasoning_new.pms)PET");
    write_text(kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
fact:burn can injure
relation:causes|fire is hot|hot can burn
)PET");
    write_text(input_file, R"PET(PAIIN:1
goal:avoid injury
observe:fire is hot
observe:hot can burn
rule:simple_causal_inference|fire is hot|hot can burn|fire can burn
rule:injury_inference|fire can burn|burn can injure|fire can injure
rule:risk_inference|fire can injure|burn can injure|injury is dangerous
)PET");
    run({((build / R"PET(petoron_ai_init_state)PET")).string(), (kb).string(), (old_state).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (old_state).string(), (kb).string(), (input_file).string(), (new_kb).string(), (cycle).string(), (transition).string(), (new_state).string()});
    const std::string text = read_text(new_kb);
    const std::vector<std::string> required = {R"PET(fact:fire can burn)PET", R"PET(fact:fire can injure)PET", R"PET(fact:injury is dangerous)PET", R"PET(fact:avoid injury completed)PET"};
    require_all(text, required);
    run({((build / R"PET(petoron_ai_verify_kb_transition)PET")).string(), (kb).string(), (input_file).string(), (cycle).string(), (new_kb).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (old_state).string(), (transition).string(), (new_state).string()});
    std::cout << "petoron_ai_recursive_reasoning_test PASS\n";
    return 0;
}
