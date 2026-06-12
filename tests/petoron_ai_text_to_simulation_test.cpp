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
    const fs::path kb = (outdir / R"PET(text_to_simulation.pkb)PET");
    const fs::path input_file = (outdir / R"PET(text_to_simulation.paiin)PET");
    const fs::path old_state = (outdir / R"PET(text_to_simulation_old.pms)PET");
    const fs::path new_kb = (outdir / R"PET(text_to_simulation_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(text_to_simulation.pcycle)PET");
    const fs::path transition = (outdir / R"PET(text_to_simulation.pkbt)PET");
    const fs::path new_state = (outdir / R"PET(text_to_simulation_new.pms)PET");
    write_text(kb, R"PET(PKB:1
fact:dark clouds visible
fact:dark clouds can indicate storm
fact:storm can damage shelter
relation:indicates|dark clouds visible|dark clouds can indicate storm
)PET");
    run({((build / R"PET(petoron_ai_text_to_input)PET")).string(), R"PET(I see dark clouds. Storm can damage shelter. Avoid danger.)PET", (input_file).string()});
    run({((build / R"PET(petoron_ai_init_state)PET")).string(), (kb).string(), (old_state).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (old_state).string(), (kb).string(), (input_file).string(), (new_kb).string(), (cycle).string(), (transition).string(), (new_state).string()});
    run({((build / R"PET(petoron_ai_verify_kb_transition)PET")).string(), (kb).string(), (input_file).string(), (cycle).string(), (new_kb).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (old_state).string(), (transition).string(), (new_state).string()});
    const std::string answer = output({((build / R"PET(petoron_ai_simulation_to_text)PET")).string(), (new_kb).string(), (input_file).string()});
    const std::vector<std::string> required = {R"PET(Goal: avoid storm)PET", R"PET(Selected action: find shelter)PET", R"PET(Expected future: safe shelter)PET", R"PET(Risk: 10)PET", R"PET(Rejected action: stay outside)PET", R"PET(Rejected future: storm exposure)PET", R"PET(Rejected risk: 90)PET"};
    require_all(answer, required);
    std::cout << "petoron_ai_text_to_simulation_test PASS\n";
    return 0;
}
