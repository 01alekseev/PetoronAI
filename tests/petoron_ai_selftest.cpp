/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/petoron_mind.hpp"

#include <cstdlib>

int main() {
    petoron_ai::PetoronMind mind;

    const auto transition =
        mind.observe("selftest observation");

    if (transition.new_root == transition.old_root) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
