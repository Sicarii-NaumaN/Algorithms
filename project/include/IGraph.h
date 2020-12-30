//
// Created by naum on 17.12.2020.
//

#ifndef TASK6_IGRAPH_H
#define TASK6_IGRAPH_H

#include <iostream>
#include <vector>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


#endif //TASK6_IGRAPH_H
