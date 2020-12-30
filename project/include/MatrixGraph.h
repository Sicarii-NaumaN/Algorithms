//
// Created by naum on 20.12.2020.
//

#ifndef TASK6_MATRIXGRAPH_H
#define TASK6_MATRIXGRAPH_H


#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int count);
    explicit MatrixGraph(const IGraph &graph);
    virtual void AddEdge(int from, int to) override ;
    virtual int VerticesCount() const override ;
    virtual std::vector<int> GetNextVertices(int vertex) const override ;
    virtual std::vector<int> GetPrevVertices(int vertex) const override ;
private:
    std::vector<std::vector<bool>> adjacency_matrix;
};

#endif //TASK6_MATRIXGRAPH_H
