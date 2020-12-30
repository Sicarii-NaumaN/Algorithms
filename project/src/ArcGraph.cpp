#include "ArcGraph.h"

ArcGraph::ArcGraph(int count) : count(count) {}

ArcGraph::ArcGraph(const IGraph &graph) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> vertices = graph.GetNextVertices(i);
        for (auto vert : vertices)
            edges.emplace_back(i, vert);
    }
}

void ArcGraph::AddEdge(int from, int to) {
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (auto edge : edges)
        if (edge.first == vertex)
            result.push_back(edge.second);
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (auto edge : edges)
        if (edge.second == vertex)
            result.push_back(edge.first);
    return result;
}