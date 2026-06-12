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

    const fs::path a_input = root / "petoron_ai_fire.paiin";
    const fs::path b_input = outdir / "petoron_ai_fire_mutated.paiin";
    const fs::path a_cycle = outdir / "mutation_a.pcycle";
    const fs::path b_cycle = outdir / "mutation_b.pcycle";

    auto text = read_text(a_input);
    replace_first(text, "fire is hot", "fire is very hot");
    write_text(b_input, text);

    run({exe(build, "petoron_ai_run_cycle"), a_input.string(), a_cycle.string()});
    run({exe(build, "petoron_ai_run_cycle"), b_input.string(), b_cycle.string()});

    const auto a_inspect = output({exe(build, "petoron_ai_inspect_cycle"), a_cycle.string()});
    const auto b_inspect = output({exe(build, "petoron_ai_inspect_cycle"), b_cycle.string()});

    const auto a_input_id = extract_value("input_id", a_inspect);
    const auto b_input_id = extract_value("input_id", b_inspect);
    const auto a_cycle_id = extract_value("cycle_id", a_inspect);
    const auto b_cycle_id = extract_value("cycle_id", b_inspect);

    if (a_input_id.empty() || b_input_id.empty()) {
        return 1;
    }

    if (a_cycle_id.empty() || b_cycle_id.empty()) {
        return 2;
    }

    if (a_input_id == b_input_id) {
        std::cerr << "input_id mutation failed\n";
        return 3;
    }

    if (a_cycle_id == b_cycle_id) {
        std::cerr << "cycle_id mutation failed\n";
        return 4;
    }

    std::cout << "PetoronAI input mutation test PASS\n";
    return 0;
}
