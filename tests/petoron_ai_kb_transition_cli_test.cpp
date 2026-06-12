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

    const fs::path old_kb = outdir / "transition_cli_old.pkb";
    const fs::path new_kb = outdir / "transition_cli_new.pkb";
    const fs::path cycle = outdir / "transition_cli_cycle.pcycle";
    const fs::path transition = outdir / "transition_cli.pkbt";
    const fs::path input_file = root / "petoron_ai_fire.paiin";

    write_text(
        old_kb,
        "PKB:1\n"
        "fact:fire is hot\n"
        "fact:hot can burn\n"
        "relation:causes|fire is hot|hot can burn\n"
    );

    run({
        (build / "petoron_ai_run_cycle_kb_update").string(),
        old_kb.string(),
        input_file.string(),
        cycle.string(),
        new_kb.string()
    });

    run({
        (build / "petoron_ai_write_kb_transition").string(),
        old_kb.string(),
        input_file.string(),
        cycle.string(),
        new_kb.string(),
        transition.string()
    });

    run({
        (build / "petoron_ai_inspect_kb_transition").string(),
        transition.string()
    });

    run({
        (build / "petoron_ai_verify_kb_transition").string(),
        old_kb.string(),
        input_file.string(),
        cycle.string(),
        new_kb.string(),
        transition.string()
    });

    std::cout << "petoron_ai_kb_transition_cli_test PASS\n";
    return 0;
}
