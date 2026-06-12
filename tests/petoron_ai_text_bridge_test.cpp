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
    const std::string text_input = R"PET(I see dark clouds. Storm can damage shelter. Avoid danger.)PET";
    const fs::path kb = (outdir / R"PET(text_bridge.pkb)PET");
    const fs::path input_file = (outdir / R"PET(text_bridge.paiin)PET");
    const fs::path old_state = (outdir / R"PET(text_bridge_old.pms)PET");
    const fs::path new_kb = (outdir / R"PET(text_bridge_new.pkb)PET");
    const fs::path cycle = (outdir / R"PET(text_bridge.pcycle)PET");
    const fs::path transition = (outdir / R"PET(text_bridge.pkbt)PET");
    const fs::path new_state = (outdir / R"PET(text_bridge_new.pms)PET");
    write_text(kb, R"PET(PKB:1
fact:dark clouds visible
fact:dark clouds can indicate storm
fact:storm can damage shelter
relation:indicates|dark clouds visible|dark clouds can indicate storm
)PET");
    run({((build / R"PET(petoron_ai_text_to_input)PET")).string(), text_input, (input_file).string()});
    run({((build / R"PET(petoron_ai_init_state)PET")).string(), (kb).string(), (old_state).string()});
    run({((build / R"PET(petoron_ai_step)PET")).string(), (old_state).string(), (kb).string(), (input_file).string(), (new_kb).string(), (cycle).string(), (transition).string(), (new_state).string()});
    const std::string text = read_text(new_kb);
    const std::vector<std::string> required = {R"PET(fact:hypothesis:storm exists)PET", R"PET(fact:storm is dangerous)PET", R"PET(fact:avoid storm completed)PET", R"PET(fact:active goal:avoid storm)PET", R"PET(fact:confidence:hypothesis:storm exists:60)PET", R"PET(fact:confidence:storm is dangerous:90)PET", R"PET(fact:explain:storm is dangerous:hypothesis:storm exists)PET", R"PET(fact:explain:avoid storm:storm is dangerous)PET", R"PET(fact:strategy:avoid storm effective)PET", R"PET(fact:strategy_score:avoid storm:1)PET"};
    require_all(text, required);
    run({((build / R"PET(petoron_ai_verify_kb_transition)PET")).string(), (kb).string(), (input_file).string(), (cycle).string(), (new_kb).string(), (transition).string()});
    run({((build / R"PET(petoron_ai_verify_mind_state_transition)PET")).string(), (old_state).string(), (transition).string(), (new_state).string()});
    const std::string answer = output({((build / R"PET(petoron_ai_kb_to_text)PET")).string(), (new_kb).string()});
    const std::vector<std::string> required_answer = {R"PET(Hypothesis: storm exists)PET", R"PET(Risk: storm is dangerous)PET", R"PET(Confidence: storm is dangerous:90)PET", R"PET(Action: avoid storm completed)PET", R"PET(Action: active goal:avoid storm)PET", R"PET(Explanation: storm is dangerous:hypothesis:storm exists)PET", R"PET(Explanation: avoid storm:storm is dangerous)PET", R"PET(Learned: avoid storm effective)PET"};
    require_all(answer, required_answer);
    std::cout << "petoron_ai_text_bridge_test PASS\n";
    return 0;
}
