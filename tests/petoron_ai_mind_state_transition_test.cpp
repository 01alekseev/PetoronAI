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

    const fs::path old_kb = outdir / "state_transition_old.pkb";
    const fs::path new_kb = outdir / "state_transition_new.pkb";
    const fs::path cycle = outdir / "state_transition_cycle.pcycle";
    const fs::path transition = outdir / "state_transition.pkbt";
    const fs::path old_state = outdir / "state_transition_old.pms";
    const fs::path new_state = outdir / "state_transition_new.pms";
    const fs::path bad_state = outdir / "state_transition_bad.pms";
    const fs::path input_file = root / "petoron_ai_fire.paiin";

    write_text(old_kb, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");

    run({exe(build, "petoron_ai_run_cycle_kb_update"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string()});
    run({exe(build, "petoron_ai_write_kb_transition"), old_kb.string(), input_file.string(), cycle.string(), new_kb.string(), transition.string()});

    const auto transition_data = read_binary(transition);
    const auto old_kb_id = slice_bytes(transition_data, 5, 32);
    const auto new_kb_id = slice_bytes(transition_data, 5 + 32 * 4, 32);
    const auto cycle_id = slice_bytes(transition_data, 5 + 32 * 2, 32);

    std::vector<unsigned char> old_state_data;
    old_state_data.insert(old_state_data.end(), {'P', 'M', 'S', 'F'});
    old_state_data.push_back(1);
    old_state_data.insert(old_state_data.end(), old_kb_id.begin(), old_kb_id.end());
    old_state_data.insert(old_state_data.end(), 32, 0);
    old_state_data.insert(old_state_data.end(), 32, 0);
    append_u64_le(old_state_data, 0);
    write_binary(old_state, old_state_data);

    run({exe(build, "petoron_ai_write_mind_state"), new_kb.string(), new_state.string(), transition.string()});
    run({exe(build, "petoron_ai_verify_mind_state_transition"), old_state.string(), transition.string(), new_state.string()});

    std::vector<unsigned char> bad_state_data;
    bad_state_data.insert(bad_state_data.end(), {'P', 'M', 'S', 'F'});
    bad_state_data.push_back(1);
    bad_state_data.insert(bad_state_data.end(), new_kb_id.begin(), new_kb_id.end());
    bad_state_data.insert(bad_state_data.end(), 32, 0);
    bad_state_data.insert(bad_state_data.end(), cycle_id.begin(), cycle_id.end());
    append_u64_le(bad_state_data, 9);
    write_binary(bad_state, bad_state_data);

    const auto rc = status({exe(build, "petoron_ai_verify_mind_state_transition"), old_state.string(), transition.string(), bad_state.string()});
    if (rc == 0) {
        return 1;
    }

    std::cout << "PetoronAI mind state transition test PASS\n";
    return 0;
}
