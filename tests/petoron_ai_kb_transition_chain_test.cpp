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

    const fs::path old_kb = outdir / "chain_old.pkb";
    const fs::path new_kb = outdir / "chain_new.pkb";
    const fs::path cycle = outdir / "chain_cycle.pcycle";
    const fs::path a = outdir / "chain_a.pkbt";
    const fs::path b = outdir / "chain_b.pkbt";
    const fs::path broken = outdir / "chain_broken.pkbt";
    const fs::path input_file = root / "petoron_ai_fire.paiin";

    write_text(old_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");

    run({exe(build, "petoron_ai_run_cycle_kb_update"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string()});
    run({exe(build, "petoron_ai_write_kb_transition"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string(), a.string()});

    auto data = read_binary(a);
    const auto new_kb_id = slice_bytes(data, 5 + 32 * 4, 32);
    overwrite_bytes(data, 5, new_kb_id);
    write_binary(b, data);

    run({exe(build, "petoron_ai_verify_kb_transition_chain"), a.string(), b.string()});

    auto broken_data = read_binary(b);
    if (broken_data.size() <= 5) {
        return 1;
    }
    broken_data[5] ^= 0x01;
    write_binary(broken, broken_data);

    const auto rc = status({exe(build, "petoron_ai_verify_kb_transition_chain"), a.string(), broken.string()});
    if (rc == 0) {
        return 1;
    }

    std::cout << "PetoronAI kb transition chain test PASS\n";
    return 0;
}
