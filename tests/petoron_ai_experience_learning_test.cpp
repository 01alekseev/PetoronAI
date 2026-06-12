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
    const fs::path old_kb = (outdir / R"PET(experience_learning_old.pkb)PET");
    const fs::path exp = (outdir / R"PET(experience_learning.pexp)PET");
    const fs::path new_kb = (outdir / R"PET(experience_learning_new.pkb)PET");
    write_text(old_kb, R"PET(PKB:1
fact:storm is dangerous
fact:strategy_score:avoid storm:5
)PET");
    write_text(exp, R"PET(PEXP:1
goal:avoid storm
action:find shelter
predicted_risk:10
actual_result:success
reward:100
)PET");
    run({((build / R"PET(petoron_ai_record_experience)PET")).string(), (old_kb).string(), (exp).string(), (new_kb).string()});
    const std::string text = read_text(new_kb);
    const std::vector<std::string> required = {R"PET(fact:storm is dangerous)PET", R"PET(fact:strategy_score:avoid storm:6)PET", R"PET(fact:experience_count:avoid storm:1)PET", R"PET(fact:success_count:avoid storm:1)PET", R"PET(fact:failure_count:avoid storm:0)PET", R"PET(fact:average_reward:avoid storm:100)PET"};
    require_all(text, required);
    require_absent_all(text, {R"PET(fact:strategy_score:avoid storm:5)PET", R"PET(fact:experience_count:avoid storm:0)PET"});
    std::cout << "petoron_ai_experience_learning_test PASS\n";
    return 0;
}
