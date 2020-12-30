//
// Created by naum on 20.12.2020.
//

#ifndef TASK6_SETGRAPH_H
#define TASK6_SETGRAPH_H

#include "IGraph.h"
#include <unordered_set>

class SetGraph : public IGraph{
public:
    explicit SetGraph(int count);

    explicit SetGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override ;

    virtual int VerticesCount() const override ;

    virtual std::vector<int> GetNextVertices(int vertex) const override ;

    virtual std::vector<int> GetPrevVertices(int vertex) const override ;

private:
    std::vector<std::unordered_set<int>> adj_list;
    std::vector<std::unordered_set<int>> adj_list_prev;
};

#endif //TASK6_SETGRAPH_H
