/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_store_file.hpp"

#include <cstdlib>
#include <filesystem>

int main() {
    namespace fs = std::filesystem;

    const fs::path path =
        fs::current_path() / "var" / "tests" / "thought_store.pts";

    fs::create_directories(path.parent_path());

    petoron_ai::ThoughtStore store;

    const auto a =
        petoron_ai::make_thought_artifact(
            "storm requires shelter",
            "storm is dangerous",
            "avoid storm",
            90
        );

    const auto b =
        petoron_ai::make_thought_artifact(
            "fire requires distance",
            "fire is dangerous",
            "avoid fire",
            80
        );

    if (!petoron_ai::add_thought(store, a)) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::add_thought(store, b)) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::add_thought(store, a)) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::write_thought_store_file(path.string(), store)) {
        return EXIT_FAILURE;
    }

    petoron_ai::ThoughtStore loaded;

    if (!petoron_ai::read_thought_store_file(path.string(), loaded)) {
        return EXIT_FAILURE;
    }

    if (loaded.thoughts.size() != 2) {
        return EXIT_FAILURE;
    }

    if (loaded.thoughts[0].id != a.id) {
        return EXIT_FAILURE;
    }

    if (loaded.thoughts[1].id != b.id) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
