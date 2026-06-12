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

    const fs::path good = outdir / "fire_test.pkb";
    write_text(good, R"PET(PKB:1
fact:fire is hot
fact:hot can burn
relation:causes|fire is hot|hot can burn
)PET");

    run({exe(build, "petoron_ai_inspect_kb"), good.string()});

    const std::vector<std::pair<std::string, std::string>> bad_cases = {
        {"empty", ""},
        {"bad_header", "BAD:1\nfact:x\n"},
        {"empty_fact", "PKB:1\nfact:\n"},
        {"bad_relation_parts", "PKB:1\nfact:a\nfact:b\nrelation:x|a\n"},
        {"extra_relation_parts", "PKB:1\nfact:a\nfact:b\nrelation:x|a|b|c\n"},
        {"missing_from_fact", "PKB:1\nfact:b\nrelation:x|a|b\n"},
        {"duplicate_fact", "PKB:1\nfact:a\nfact:a\n"},
        {"blank_line", "PKB:1\n\nfact:a\n"},
        {"unknown_line", "PKB:1\nhello:a\n"}
    };

    for (const auto& entry : bad_cases) {
        const auto path = outdir / ("bad_kb_" + entry.first + ".pkb");
        write_text(path, entry.second);
        const auto rc = status({exe(build, "petoron_ai_inspect_kb"), path.string()});
        if (rc == 0) {
            std::cerr << "bad kb accepted: " << entry.first << "\n";
            return 1;
        }
    }

    std::cout << "PetoronAI kb test PASS\n";
    return 0;
}
