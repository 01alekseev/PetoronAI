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
    const fs::path valid = (outdir / R"PET(petoron_ai_ctest_valid.pcycle)PET");
    const fs::path tampered = (outdir / R"PET(petoron_ai_ctest_tampered.pcycle)PET");
    run({((build / R"PET(petoron_ai_run_cycle)PET")).string(), (input_file).string(), (valid).string()});
    run({((build / R"PET(petoron_ai_verify_cycle)PET")).string(), (valid).string()});
    auto data = read_binary(valid);
    if (data.empty()) { return 1; }
    data.back() ^= 0x01;
    write_binary(tampered, data);
    const int result_returncode = status({((build / R"PET(petoron_ai_verify_cycle)PET")).string(), (tampered).string()});
    if (result_returncode == 0) { return 1; }
    std::cout << "petoron_ai_tamper_test PASS\n";
    return 0;
}
