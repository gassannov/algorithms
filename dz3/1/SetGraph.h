//
// Created by Марат Гасанов on 24.05.2022.
//

#ifndef SET_GRAPH_H
#define SET_GRAPH_H

#include "vector"
#include "IGraph.h"
#include "iostream"
#include "set"


class SetGraph : public IGraph{
    std::vector<std::set<int>> vertexes;
public:
    explicit SetGraph(int vertCount);
    SetGraph(const IGraph& graph);
    void AddEdge(int from, int to) override;
    int VerticesCount() const override {return vertexes.size();}
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override ;
    ~SetGraph();
};

#endif
