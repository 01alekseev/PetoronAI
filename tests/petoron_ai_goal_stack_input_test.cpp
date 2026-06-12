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

    const fs::path base = outdir / "goal_stack_base.paiin";
    const fs::path stack = outdir / "goal_stack_input.paiin";

    write_text(base, R"PET(PAIIN:1
goal:auto
observe:dark clouds visible
observe:dark clouds can indicate storm
observe:storm can damage shelter
rule:hypothesis_inference|dark clouds visible|dark clouds can indicate storm|hypothesis:storm exists
rule:risk_inference|hypothesis:storm exists|storm can damage shelter|storm is dangerous
)PET");

    write_text(stack, R"PET(PAIIN:1
goal:auto
goal_candidate:avoid danger
goal_candidate:protect shelter
observe:dark clouds visible
observe:dark clouds can indicate storm
observe:storm can damage shelter
rule:hypothesis_inference|dark clouds visible|dark clouds can indicate storm|hypothesis:storm exists
rule:risk_inference|hypothesis:storm exists|storm can damage shelter|storm is dangerous
)PET");

    const auto base_out = output({exe(build, "petoron_ai_inspect_input"), base.string()});
    const auto stack_out = output({exe(build, "petoron_ai_inspect_input"), stack.string()});

    require_all(stack_out, {
        "valid: true",
        "goal: auto",
        "goal_candidates: 2",
        "goal_candidate: avoid danger",
        "goal_candidate: protect shelter",
        "observations: 3",
        "rules: 2"
    });

    const auto base_id = extract_value("input_id", base_out);
    const auto stack_id = extract_value("input_id", stack_out);

    if (base_id.empty() || stack_id.empty()) {
        return 2;
    }

    if (base_id == stack_id) {
        std::cerr << "input ids should differ\n";
        return 3;
    }

    std::cout << "PetoronAI goal stack input test PASS\n";
    return 0;
}
