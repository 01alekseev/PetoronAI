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

    const auto out =
        output({
            (build / "petoron_ai_ask_with_thoughts").string(),
            (root / "var" / "tests" / "future_simulator.pkb").string(),
            (root / "var" / "tests" / "thought_store.pts").string(),
            "I see dark clouds. Storm can damage shelter. Avoid danger."
        });

    require_contains(out, "Goal: avoid storm");
    require_contains(out, "Thought: storm requires shelter");
    require_contains(out, "Thought reason: storm is dangerous");
    require_contains(out, "Thought confidence: 90");
    require_contains(out, "Selected action: find shelter");
    require_contains(out, "Expected future: safe shelter");
    require_contains(out, "Risk: 10");
    require_contains(out, "Meta explanation: selected strategy has verified thought path");
    require_contains(out, "Meta confidence: 90");

    return 0;
}
