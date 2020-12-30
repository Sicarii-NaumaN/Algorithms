#include "SetGraph.h"

SetGraph::SetGraph(int count) : adj_list(count), adj_list_prev(count) {}

SetGraph::SetGraph(const IGraph &graph) : adj_list(graph.VerticesCount()), adj_list_prev(graph.VerticesCount()) {
    for (int i = 0; i < adj_list.size(); ++i) {
        std::vector<int> vertices = graph.GetNextVertices(i);
        for (auto v : vertices){
            adj_list[i].insert(v);
            adj_list_prev[v].insert(i);
        }

    }
}

void SetGraph::AddEdge(int from, int to) {
    adj_list[from].insert(to);
    adj_list_prev[to].insert(from);
    return;
}

int SetGraph::VerticesCount() const {
    return adj_list.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    std::unordered_set<int> vertices = adj_list[vertex];
    result.reserve(vertices.size());
    for (auto v : vertices)
        result.push_back(v);
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    std::unordered_set<int> vertices = adj_list_prev[vertex];
    result.reserve(vertices.size());
    for (auto v : vertices)
        result.push_back(v);
    return result;
}