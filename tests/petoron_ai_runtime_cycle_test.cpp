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
    const fs::path input_file = (root / R"PET(petoron_ai_fire.paiin)PET");
    const fs::path cycle_file = (outdir / R"PET(petoron_ai_runtime_cycle.pcycle)PET");
    run({((build / R"PET(petoron_ai_inspect_input)PET")).string(), (input_file).string()});
    run({((build / R"PET(petoron_ai_run_cycle)PET")).string(), (input_file).string(), (cycle_file).string()});
    run({((build / R"PET(petoron_ai_verify_cycle)PET")).string(), (cycle_file).string()});
    run({((build / R"PET(petoron_ai_verify_cycle_input)PET")).string(), (input_file).string(), (cycle_file).string()});
    run({((build / R"PET(petoron_ai_check)PET")).string(), (input_file).string(), (cycle_file).string()});
    run({((build / R"PET(petoron_ai_inspect_cycle)PET")).string(), (cycle_file).string()});
    std::cout << "petoron_ai_runtime_cycle_test PASS\n";
    return 0;
}
