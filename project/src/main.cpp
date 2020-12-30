#include <iostream>


#include "ListGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include "MatrixGraph.h"


int main() {
    ListGraph graph(6);
    MatrixGraph graph_m(6);
    SetGraph graph_s(6);
    ArcGraph graph_a(6);

    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 5);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(4, 2);

    graph_m.AddEdge(0, 1);
    graph_m.AddEdge(1, 2);
    graph_m.AddEdge(1, 5);
    graph_m.AddEdge(2, 3);
    graph_m.AddEdge(3, 4);
    graph_m.AddEdge(4, 2);

    graph_a.AddEdge(0, 1);
    graph_a.AddEdge(1, 2);
    graph_a.AddEdge(1, 5);
    graph_a.AddEdge(2, 3);
    graph_a.AddEdge(3, 4);
    graph_a.AddEdge(4, 2);

    graph_s.AddEdge(0, 1);
    graph_s.AddEdge(1, 2);
    graph_s.AddEdge(1, 5);
    graph_s.AddEdge(2, 3);
    graph_s.AddEdge(3, 4);
    graph_s.AddEdge(4, 2);

    dfs(graph, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "------------------------" << std::endl;
    bfs(graph, [](int v) {
        std::cout << v << std::endl;
    });


    return 0;
}