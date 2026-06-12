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

    const fs::path kb = outdir / "init_state.pkb";
    const fs::path state = outdir / "init_state.pms";

    write_text(kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");

    run({exe(build, "petoron_ai_init_state"), kb.string(), state.string()});

    const auto out = output({exe(build, "petoron_ai_inspect_mind_state"), state.string()});
    const std::string zero64(64, '0');

    require_contains(out, "cycle_count: 0");
    require_contains(out, "transition_chain_id: " + zero64);
    require_contains(out, "last_cycle_id: " + zero64);

    std::cout << "PetoronAI init state test PASS\n";
    return 0;
}
