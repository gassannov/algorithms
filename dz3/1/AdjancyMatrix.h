//
// Created by Марат Гасанов on 24.05.2022.
//
#include <vector>
#include "IGraph.h"

#ifndef DZ3_ADJANCYMATRIX_H
#define DZ3_ADJANCYMATRIX_H


class AdjancyMatrix: public IGraph{
    size_t size;
    std::vector<std::vector<int>> matrix;
public:
    AdjancyMatrix(int vertCnt);
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
    void buildfromIGraph(const IGraph& graph);

};


#endif //DZ3_ADJANCYMATRIX_H
