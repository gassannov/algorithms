//
// Created by Марат Гасанов on 24.05.2022.
//

#ifndef DZ3_ADJANCYLIST_H
#define DZ3_ADJANCYLIST_H
#include "vector"
#include "IGraph.h"
#include "iostream"


class AdjancyListGraph : public IGraph{
    std::vector<std::vector<int>> vertexes;
public:
    explicit AdjancyListGraph(int vertCount) : vertexes(vertCount){};
    void AddEdge(int from, int to) override;
    int VerticesCount() const override {return vertexes.size();}
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override ;
    void buildBromIGRaph(const IGraph& graph);
    ~AdjancyListGraph();
};


#endif //DZ3_ADJANCYLIST_H
