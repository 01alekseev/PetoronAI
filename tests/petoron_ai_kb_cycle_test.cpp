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
    const fs::path kb = (outdir / R"PET(kb_cycle.pkb)PET");
    const fs::path input_file = (root / R"PET(petoron_ai_fire.paiin)PET");
    const fs::path cycle = (outdir / R"PET(kb_cycle.pcycle)PET");
    write_text(kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");
    run({((build / R"PET(petoron_ai_run_cycle_kb)PET")).string(), (kb).string(), (input_file).string(), (cycle).string()});
    run({((build / R"PET(petoron_ai_check)PET")).string(), (input_file).string(), (cycle).string()});
    run({((build / R"PET(petoron_ai_verify_cycle_kb_input)PET")).string(), (kb).string(), (input_file).string(), (cycle).string()});
    std::cout << "petoron_ai_kb_cycle_test PASS\n";
    return 0;
}
