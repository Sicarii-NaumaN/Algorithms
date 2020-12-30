#include "MatrixGraph.h"

void MatrixGraph::AddEdge(int from, int to) {
    adjacency_matrix[from][to] = true;
}

MatrixGraph::MatrixGraph(int count) : adjacency_matrix(count) {
    for(int i = 0; i < count; ++i)
        adjacency_matrix[i].assign(count, false);
}

MatrixGraph::MatrixGraph(const IGraph &graph) : adjacency_matrix(graph.VerticesCount()) {
    for(int i = 0; i < adjacency_matrix.size(); ++i)
        adjacency_matrix[i].assign(adjacency_matrix.size(), false);

    for(int i = 0; i < adjacency_matrix.size(); ++i){
        std::vector<int> vertices = graph.GetNextVertices(i);
        for(int v : vertices)
            adjacency_matrix[i][v] = true;
    }
}

int MatrixGraph::VerticesCount() const {
    return adjacency_matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    for(int i = 0; i < adjacency_matrix.size(); i++){
        if(adjacency_matrix[vertex][i])
            result.push_back(i);
    }
    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for(int i = 0; i < adjacency_matrix.size(); i++){
        if(adjacency_matrix[i][vertex])
            result.push_back(i);
    }
    return result;
}