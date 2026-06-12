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
    const fs::path good_kb = (outdir / R"PET(good_kb_mismatch.pkb)PET");
    const fs::path bad_kb = (outdir / R"PET(bad_kb_mismatch.pkb)PET");
    const fs::path input_file = (root / R"PET(petoron_ai_fire.paiin)PET");
    const fs::path cycle = (outdir / R"PET(kb_input_mismatch.pcycle)PET");
    write_text(good_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");
    write_text(bad_kb, R"PET(PKB:1
fact:water is cold
fact:cold can freeze
relation:causes|water is cold|cold can freeze
)PET");
    run({((build / R"PET(petoron_ai_run_cycle_kb)PET")).string(), (good_kb).string(), (input_file).string(), (cycle).string()});
    run({((build / R"PET(petoron_ai_verify_cycle_kb_input)PET")).string(), (good_kb).string(), (input_file).string(), (cycle).string()});
    const int result_returncode = status({((build / R"PET(petoron_ai_verify_cycle_kb_input)PET")).string(), (bad_kb).string(), (input_file).string(), (cycle).string()});
    if (result_returncode == 0) { return 1; }
    std::cout << "petoron_ai_kb_input_mismatch_test PASS\n";
    return 0;
}
