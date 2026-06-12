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
            "storm requires shelter",
            "storm is dangerous",
            "avoid storm",
            90
        );

    const auto c =
        petoron_ai::make_thought_artifact(
            "stay inside shelter",
            "shelter reduces exposure",
            "avoid storm",
            100
        );

    const auto x =
        petoron_ai::make_thought_artifact(
            "fire requires distance",
            "fire is dangerous",
            "avoid fire",
            80
        );

    const petoron_ai::ThoughtEdge ab{a.id, b.id, 10};
    const petoron_ai::ThoughtEdge bc{b.id, c.id, 10};

    const auto graph =
        petoron_ai::make_thought_graph(
            {a, b, c, x},
            {ab, bc}
        );

    const auto graph2 =
        petoron_ai::make_thought_graph(
            {a, b, c, x},
            {ab, bc}
        );

    if (graph.nodes.size() != 4) {
        return EXIT_FAILURE;
    }

    if (graph.edges.size() != 2) {
        return EXIT_FAILURE;
    }

    if (graph.id != graph2.id) {
        return EXIT_FAILURE;
    }

    if (!petoron_ai::has_thought_path(graph, a.id, c.id)) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::has_thought_path(graph, c.id, a.id)) {
        return EXIT_FAILURE;
    }

    if (petoron_ai::has_thought_path(graph, a.id, x.id)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
