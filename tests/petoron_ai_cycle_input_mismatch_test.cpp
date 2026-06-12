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
    const fs::path good_input = (root / R"PET(petoron_ai_fire.paiin)PET");
    const fs::path bad_input = (outdir / R"PET(petoron_ai_wrong_input.paiin)PET");
    const fs::path cycle_file = (outdir / R"PET(petoron_ai_input_mismatch.pcycle)PET");
    write_text(bad_input, R"PET(PAIIN:1
goal:avoid danger
observe:water is cold
observe:cold can freeze
rule:freeze_inference|water is cold|cold can freeze|water can freeze
)PET");
    run({((build / R"PET(petoron_ai_run_cycle)PET")).string(), (good_input).string(), (cycle_file).string()});
    run({((build / R"PET(petoron_ai_verify_cycle)PET")).string(), (cycle_file).string()});
    const int result_returncode = status({((build / R"PET(petoron_ai_verify_cycle_input)PET")).string(), (bad_input).string(), (cycle_file).string()});
    if (result_returncode == 0) { return 1; }
    std::cout << "petoron_ai_cycle_input_mismatch_test PASS\n";
    return 0;
}
