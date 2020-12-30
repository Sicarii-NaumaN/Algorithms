//
// Created by naum on 20.12.2020.
//

#ifndef TASK6_LISTGRAPH_H
#define TASK6_LISTGRAPH_H

#include "IGraph.h"

class ListGraph : public IGraph {
public:
    ListGraph(size_t verticesCount);

    ListGraph(const IGraph&);

    virtual ~ListGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override { return graph.size(); }

    std::vector<int> GetNextVertices(int vertex) const  override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector <std::vector<int> > graph;
};

void dfs_aux(const IGraph& graph, int vertex, std::vector<bool>& visited, void (*callback)(int v));
void dfs(const IGraph& graph, void (*callback)(int v));
void bfs(const IGraph& graph, void (*callback)(int v));

#endif //TASK6_LISTGRAPH_H
