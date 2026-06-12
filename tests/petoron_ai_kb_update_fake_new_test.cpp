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
    const fs::path old_kb = (outdir / R"PET(fake_new_old.pkb)PET");
    const fs::path fake_new_kb = (outdir / R"PET(fake_new_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(fake_new_cycle.pcycle)PET");
    const fs::path input_file = (root / R"PET(petoron_ai_fire.paiin)PET");
    write_text(old_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");
    write_text(fake_new_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");
    run({((build / R"PET(petoron_ai_run_cycle_kb)PET")).string(), (old_kb).string(), (input_file).string(), (cycle).string()});
    const int result_returncode = status({((build / R"PET(petoron_ai_verify_kb_update)PET")).string(), (old_kb).string(), (input_file).string(), (cycle).string(), (fake_new_kb).string()});
    if (result_returncode == 0) { return 1; }
    std::cout << "petoron_ai_kb_update_fake_new_test PASS\n";
    return 0;
}
