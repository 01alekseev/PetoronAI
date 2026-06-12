/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_graph.hpp"

#include <cstdlib>

int main() {
    const auto a =
        petoron_ai::make_thought_artifact(
            "storm exists",
            "dark clouds indicate storm",
            "avoid storm",
            80
        );

    const auto b =
        petoron_ai::make_thought_artifact(
            "find shelter",
            "shelter reduces storm exposure",
            "avoid storm",
            90
        );

    const auto c =
        petoron_ai::make_thought_artifact(
            "stay inside shelter",
            "inside shelter is safer",
            "avoid storm",
            100
        );

    const auto d =
        petoron_ai::make_thought_artifact(
            "call rescue",
            "rescue may help later",
            "avoid storm",
            40
        );

    const auto graph =
        petoron_ai::make_thought_graph(
            {a, b, c, d},
            {
                {a.id, b.id, 90},
                {b.id, c.id, 100},
                {a.id, d.id, 40}
            }
        );

    const auto path =
        petoron_ai::best_thought_path(
            graph,
            a.id
        );

    if (!path.found) {
        return EXIT_FAILURE;
    }

    if (path.nodes.size() != 3) {
        return EXIT_FAILURE;
    }

    if (path.score != 190) {
        return EXIT_FAILURE;
    }

    if (path.nodes[0] != a.id) {
        return EXIT_FAILURE;
    }

    if (path.nodes[1] != b.id) {
        return EXIT_FAILURE;
    }

    if (path.nodes[2] != c.id) {
        return EXIT_FAILURE;
    }

    const auto missing =
        petoron_ai::best_thought_path(
            graph,
            c.id
        );

    if (missing.found) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
