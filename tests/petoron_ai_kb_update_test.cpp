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

    const fs::path old_kb = outdir / "update_old.pkb";
    const fs::path new_kb = outdir / "update_new.pkb";
    const fs::path cycle = outdir / "update_cycle.pcycle";
    const fs::path transition = outdir / "update_transition.pkbt";
    const fs::path input_file = root / "petoron_ai_fire.paiin";

    write_text(old_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");

    run({exe(build, "petoron_ai_run_cycle_kb_update"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string()});

    const auto old_inspect = output({exe(build, "petoron_ai_inspect_kb"), old_kb.string()});
    const auto new_inspect = output({exe(build, "petoron_ai_inspect_kb"), new_kb.string()});

    const auto old_facts = extract_value("facts", old_inspect);
    const auto old_root = extract_value("root", old_inspect);
    const auto new_root = extract_value("root", new_inspect);

    if (old_facts != "2") {
        return 1;
    }

    const auto new_text = read_text(new_kb);
    require_all(new_text, {"fact:avoid fire completed", "fact:plan succeeded"});

    if (old_root == new_root) {
        return 3;
    }

    run({exe(build, "petoron_ai_verify_cycle_kb_input"), old_kb.string(), input_file.string(), cycle.string()});
    run({exe(build, "petoron_ai_verify_kb_update"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string()});
    run({exe(build, "petoron_ai_write_kb_transition"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string(), transition.string()});
    run({exe(build, "petoron_ai_verify_kb_transition"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string(), transition.string()});

    std::cout << "PetoronAI kb update test PASS\n";
    return 0;
}
