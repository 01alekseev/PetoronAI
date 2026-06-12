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
    const fs::path old_kb = (outdir / R"PET(wrong_delta_old.pkb)PET");
    const fs::path wrong_new_kb = (outdir / R"PET(wrong_delta_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(wrong_delta_cycle.pcycle)PET");
    const fs::path input_file = (root / R"PET(petoron_ai_fire.paiin)PET");
    write_text(old_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");
    write_text(wrong_new_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
fact:wrong learned fact
relation:causes|fire is hot|hot can burn
)PET");
    run({((build / R"PET(petoron_ai_run_cycle_kb_update)PET")).string(), (old_kb).string(), (input_file).string(), (cycle).string(), ((outdir / R"PET(wrong_delta_real_new.pkb)PET")).string()});
    const int result_returncode = status({((build / R"PET(petoron_ai_verify_kb_update)PET")).string(), (old_kb).string(), (input_file).string(), (cycle).string(), (wrong_new_kb).string()});
    if (result_returncode == 0) { return 1; }
    std::cout << "petoron_ai_kb_update_wrong_delta_test PASS\n";
    return 0;
}
