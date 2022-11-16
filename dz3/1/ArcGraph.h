//
// Created by Марат Гасанов on 24.05.2022.
//

#ifndef DZ3_ARCGRAPH_H
#define DZ3_ARCGRAPH_H
#include "vector"
#include "IGraph.h"
#include "set"

class ArcGraph: public IGraph{
public:
    ArcGraph(const IGraph&);
    ArcGraph(int verticesCount):vertCnt(verticesCount){};
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> pairs;
    int vertCnt;
};


#endif //DZ3_ARCGRAPH_H
