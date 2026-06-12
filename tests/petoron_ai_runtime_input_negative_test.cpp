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

    const std::vector<std::pair<std::string, std::string>> cases = {
        {"empty", ""},
        {"missing_header", "goal:avoid danger\nobserve:fire is hot\nrule:a|b|c|d\n"},
        {"missing_goal", "PAIIN:1\nobserve:fire is hot\n"},
        {"missing_observe", "PAIIN:1\ngoal:avoid danger\nrule:a|b|c|d\n"},
        {"missing_rule", "PAIIN:1\ngoal:avoid danger\nobserve:fire is hot\n"},
        {"empty_goal", "PAIIN:1\ngoal:\nobserve:fire is hot\nrule:a|b|c|d\n"},
        {"empty_observe", "PAIIN:1\ngoal:avoid danger\nobserve:\nrule:a|b|c|d\n"},
        {"empty_rule", "PAIIN:1\ngoal:avoid danger\nobserve:fire is hot\nrule:\n"},
        {"bad_rule_parts", "PAIIN:1\ngoal:avoid danger\nobserve:fire is hot\nrule:a|b|c\n"},
        {"extra_rule_parts", "PAIIN:1\ngoal:avoid danger\nobserve:fire is hot\nrule:a|b|c|d|e\n"},
        {"duplicate_goal", "PAIIN:1\ngoal:a\ngoal:b\nobserve:x\nrule:a|b|c|d\n"},
        {"unknown_line", "PAIIN:1\ngoal:a\nobserve:x\nhello:y\nrule:a|b|c|d\n"},
        {"blank_line", "PAIIN:1\ngoal:a\n\nobserve:x\nrule:a|b|c|d\n"}
    };

    for (const auto& entry : cases) {
        const auto path = outdir / ("bad_" + entry.first + ".paiin");
        const auto out = outdir / ("bad_" + entry.first + ".pcycle");
        write_text(path, entry.second);
        const auto rc = status({exe(build, "petoron_ai_run_cycle"), path.string(), out.string()});
        if (rc == 0) {
            std::cerr << "negative case failed: " << entry.first << "\n";
            return 1;
        }
    }

    std::cout << "PetoronAI runtime input negative test PASS\n";
    return 0;
}
