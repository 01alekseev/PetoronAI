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
    const fs::path kb = (outdir / R"PET(ask_experience_weight.pkb)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is dangerous
fact:fire is dangerous
fact:confidence:storm is dangerous:20
fact:confidence:fire is dangerous:90
fact:experience_count:avoid storm:10
fact:success_count:avoid storm:10
fact:failure_count:avoid storm:0
fact:average_reward:avoid storm:100
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_ask)PET")).string(), (kb).string(), R"PET(I see dark clouds and smoke. Storm can damage shelter. Avoid danger.)PET"});
    const std::vector<std::string> required = {R"PET(Goal: avoid storm)PET", R"PET(Selected action: find shelter)PET", R"PET(Expected future: safe shelter)PET", R"PET(Risk: 10)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_ask_experience_weight_test PASS\n";
    return 0;
}
