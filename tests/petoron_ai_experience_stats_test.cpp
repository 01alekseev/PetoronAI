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
    const fs::path kb = (outdir / R"PET(experience_stats.pkb)PET");
    write_text(kb, R"PET(PKB:1
fact:storm is dangerous
fact:strategy_score:avoid storm:6
fact:experience_count:avoid storm:1
fact:success_count:avoid storm:1
fact:failure_count:avoid storm:0
fact:average_reward:avoid storm:100
)PET");
    const std::string out = output({((build / R"PET(petoron_ai_experience_stats)PET")).string(), (kb).string(), R"PET(avoid storm)PET"});
    const std::vector<std::string> required = {R"PET(goal: avoid storm)PET", R"PET(experience_count: 1)PET", R"PET(success_count: 1)PET", R"PET(failure_count: 0)PET", R"PET(success_rate: 100)PET", R"PET(average_reward: 100)PET"};
    require_all(out, required);
    std::cout << "petoron_ai_experience_stats_test PASS\n";
    return 0;
}
