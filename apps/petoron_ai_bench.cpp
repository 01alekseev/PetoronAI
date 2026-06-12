/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct BenchResult {
    std::string name;
    std::vector<double> values;
};

static int run_cmd(
    const std::string& cmd
) {
    return std::system((cmd + " > /dev/null 2>&1").c_str());
}

static double time_cmd_ms(
    const std::string& cmd
) {
    const auto start = std::chrono::steady_clock::now();
    const int rc = run_cmd(cmd);
    const auto end = std::chrono::steady_clock::now();

    if (rc != 0) {
        std::cerr << "command failed: " << cmd << "\n";
        std::exit(2);
    }

    return std::chrono::duration<double, std::milli>(end - start).count();
}

static double percentile(
    std::vector<double> values,
    double p
) {
    std::sort(values.begin(), values.end());
    const auto index = static_cast<std::size_t>((values.size() * p) - 1.0);
    return values[index];
}

static void print_result(
    const BenchResult& result
) {
    auto values = result.values;
    std::sort(values.begin(), values.end());

    const auto sum =
        std::accumulate(values.begin(), values.end(), 0.0);

    const auto avg = sum / static_cast<double>(values.size());
    const auto p50 = values[values.size() / 2];
    const auto p95 = percentile(values, 0.95);

    std::cout << "case: " << result.name << "\n";
    std::cout << "runs: " << values.size() << "\n";
    std::cout << "min_ms: " << values.front() << "\n";
    std::cout << "p50_ms: " << p50 << "\n";
    std::cout << "avg_ms: " << avg << "\n";
    std::cout << "p95_ms: " << p95 << "\n";
    std::cout << "max_ms: " << values.back() << "\n";
}

static BenchResult measure(
    const std::string& name,
    int runs,
    const std::function<double()>& fn
) {
    BenchResult result;
    result.name = name;

    for (int i = 0; i < runs; ++i) {
        result.values.push_back(fn());
    }

    return result;
}

int main() {
    const int runs = 50;

    fs::create_directories("var/bench");

    const std::string old_kb = "var/bench/bench_old.pkb";
    const std::string old_state = "var/bench/bench_old.pms";
    const std::string new_kb = "var/bench/bench_new.pkb";
    const std::string cycle = "var/bench/bench.pcycle";
    const std::string transition = "var/bench/bench.pkbt";
    const std::string new_state = "var/bench/bench_new.pms";
    const std::string input = "petoron_ai_fire.paiin";

    {
        std::ofstream out(old_kb, std::ios::binary);
        out << "PKB:1\n";
        out << "fact:fire is hot\n";
        out << "fact:hot can burn\n";
        out << "relation:causes|fire is hot|hot can burn\n";
    }

    const std::string init_cmd =
        "./build/petoron_ai_init_state " +
        old_kb + " " +
        old_state;

    const std::string step_cmd =
        "./build/petoron_ai_step " +
        old_state + " " +
        old_kb + " " +
        input + " " +
        new_kb + " " +
        cycle + " " +
        transition + " " +
        new_state;

    const std::string verify_kb_cmd =
        "./build/petoron_ai_verify_kb_transition " +
        old_kb + " " +
        input + " " +
        cycle + " " +
        new_kb + " " +
        transition;

    const std::string verify_mind_cmd =
        "./build/petoron_ai_verify_mind_state_transition " +
        old_state + " " +
        transition + " " +
        new_state;

    const std::string ask_kb = "var/bench/ask_bench_world.pkb";

    {
        std::ofstream out(ask_kb, std::ios::binary);
        out << "PKB:1\n";
        out << "fact:storm is dangerous\n";
        out << "fact:confidence:storm is dangerous:90\n";
        out << "fact:strategy_score:avoid storm:5\n";
    }

    const std::string ask_cmd =
        "./build/petoron_ai_ask " +
        ask_kb +
        " \"I see dark clouds. Storm can damage shelter. Avoid danger.\"";

    std::vector<BenchResult> results;

    results.push_back(measure("init_state", runs, [&]() {
        return time_cmd_ms(init_cmd);
    }));

    results.push_back(measure("step_end_to_end", runs, [&]() {
        run_cmd(init_cmd);
        return time_cmd_ms(step_cmd);
    }));

    results.push_back(measure("verify_kb_transition", runs, [&]() {
        run_cmd(init_cmd);
        run_cmd(step_cmd);
        return time_cmd_ms(verify_kb_cmd);
    }));

    results.push_back(measure("verify_mind_state_transition", runs, [&]() {
        run_cmd(init_cmd);
        run_cmd(step_cmd);
        return time_cmd_ms(verify_mind_cmd);
    }));

    results.push_back(measure("ask_end_to_end", runs, [&]() {
        return time_cmd_ms(ask_cmd);
    }));

    std::cout << "PetoronAI C++ benchmark\n";
    std::cout << "runs_per_case: " << runs << "\n";

    for (const auto& result : results) {
        print_result(result);
    }

    std::cout << "artifact_sizes_bytes:\n";

    for (const auto& path : {
        old_kb,
        old_state,
        new_kb,
        cycle,
        transition,
        new_state
    }) {
        if (fs::exists(path)) {
            std::cout << fs::path(path).filename().string()
                      << ": "
                      << fs::file_size(path)
                      << "\n";
        }
    }

    return 0;
}
