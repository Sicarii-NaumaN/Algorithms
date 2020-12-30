//
// Created by naum on 20.12.2020.
//

#ifndef TASK6_ARCGRAPH_H
#define TASK6_ARCGRAPH_H

#include "IGraph.h"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int count);
    explicit ArcGraph(const IGraph &graph); 
    virtual void AddEdge(int from, int to) override ;
    virtual int VerticesCount() const override ;
    virtual std::vector<int> GetNextVertices(int vertex) const override ;
    virtual std::vector<int> GetPrevVertices(int vertex) const override ;
private:
    int count;
    std::vector<std::pair<int, int>> edges;
};

#endif //TASK6_ARCGRAPH_H
