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
    const fs::path old_kb = (outdir / R"PET(mind_state_old.pkb)PET");
    const fs::path new_kb = (outdir / R"PET(mind_state_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(mind_state_cycle.pcycle)PET");
    const fs::path transition = (outdir / R"PET(mind_state.pkbt)PET");
    const fs::path state = (outdir / R"PET(mind_state.pms)PET");
    const fs::path input_file = (root / R"PET(petoron_ai_fire.paiin)PET");
    write_text(old_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");
    run({((build / R"PET(petoron_ai_run_cycle_kb_update)PET")).string(), (old_kb).string(), (input_file).string(), (cycle).string(), (new_kb).string()});
    run({((build / R"PET(petoron_ai_write_kb_transition)PET")).string(), (old_kb).string(), (input_file).string(), (cycle).string(), (new_kb).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_write_mind_state)PET")).string(), (new_kb).string(), (state).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_inspect_mind_state)PET")).string(), (state).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state)PET")).string(), (new_kb).string(), (state).string(), (transition).string()});
    const fs::path tampered = (outdir / R"PET(mind_state_tampered.pms)PET");
    auto data = read_binary(state);
    if (data.empty()) { return 1; }
    data.back() ^= 0x01;
    write_binary(tampered, data);
    const int result_returncode = status({((build / R"PET(petoron_ai_verify_mind_state)PET")).string(), (new_kb).string(), (tampered).string(), (transition).string()});
    if (result_returncode == 0) { return 1; }
    std::cout << "petoron_ai_mind_state_cli_test PASS\n";
    return 0;
}
