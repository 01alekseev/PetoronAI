/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/thought/thought_graph.hpp"

#include "petoron_ai/memory_graph.hpp"

namespace petoron_ai {

static bool digest_equal(
    const MemoryDigest& a,
    const MemoryDigest& b
) {
    return a == b;
}

ThoughtGraph make_thought_graph(
    const std::vector<ThoughtArtifact>& nodes,
    const std::vector<ThoughtEdge>& edges
) {
    MemoryGraph graph;

    for (const auto& node : nodes) {
        MemoryNode item;
        item.type = "thought_node";
        item.payload =
            node.source_goal + "|" +
            node.thought + "|" +
            node.reason + "|" +
            std::to_string(node.confidence);

        graph.nodes.push_back(item);
    }

    for (const auto& edge : edges) {
        MemoryNode item;
        item.type = "thought_edge";
        item.payload =
            std::to_string(edge.weight);

        graph.nodes.push_back(item);
    }

    ThoughtGraph out;
    out.nodes = nodes;
    out.edges = edges;
    out.id = commit_memory_graph(graph);

    return out;
}

bool has_thought_path(
    const ThoughtGraph& graph,
    const MemoryDigest& from,
    const MemoryDigest& to
) {
    if (digest_equal(from, to)) {
        return true;
    }

    std::vector<MemoryDigest> frontier;
    std::vector<MemoryDigest> visited;

    frontier.push_back(from);

    while (!frontier.empty()) {
        const auto current = frontier.back();
        frontier.pop_back();

        bool seen = false;

        for (const auto& item : visited) {
            if (digest_equal(item, current)) {
                seen = true;
                break;
            }
        }

        if (seen) {
            continue;
        }

        visited.push_back(current);

        for (const auto& edge : graph.edges) {
            if (!digest_equal(edge.from, current)) {
                continue;
            }

            if (digest_equal(edge.to, to)) {
                return true;
            }

            frontier.push_back(edge.to);
        }
    }

    return false;
}

}

namespace petoron_ai {

ThoughtPath best_thought_path(
    const ThoughtGraph& graph,
    const MemoryDigest& start
) {
    ThoughtPath best;

    for (const auto& edge : graph.edges) {
        if (edge.from != start) {
            continue;
        }

        ThoughtPath candidate;
        candidate.nodes.push_back(edge.from);
        candidate.nodes.push_back(edge.to);
        candidate.score = edge.weight;
        candidate.found = true;

        MemoryDigest current = edge.to;
        bool extended = true;

        while (extended) {
            extended = false;

            const ThoughtEdge* best_next = nullptr;

            for (const auto& next : graph.edges) {
                if (next.from != current) {
                    continue;
                }

                if (best_next == nullptr || next.weight > best_next->weight) {
                    best_next = &next;
                }
            }

            if (best_next != nullptr) {
                candidate.nodes.push_back(best_next->to);
                candidate.score += best_next->weight;
                current = best_next->to;
                extended = true;
            }
        }

        if (!best.found || candidate.score > best.score) {
            best = candidate;
        }
    }

    return best;
}

}
