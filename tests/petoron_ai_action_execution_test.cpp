/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/runtime/action_execution.hpp"

#include <cstdlib>

int main() {
    const auto shelter =
        petoron_ai::execute_action(
            "find shelter"
        );

    if (!shelter.success) {
        return EXIT_FAILURE;
    }

    if (shelter.outcome != "safe shelter reached") {
        return EXIT_FAILURE;
    }

    const auto unknown =
        petoron_ai::execute_action(
            "unknown action"
        );

    if (unknown.success) {
        return EXIT_FAILURE;
    }

    if (unknown.outcome != "action unknown") {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
