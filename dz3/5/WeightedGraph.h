//
// Created by Марат Гасанов on 29.05.2022.
//

#ifndef DZ3_WEIGHTEDGRAPH_H
#define DZ3_WEIGHTEDGRAPH_H
#include "vector"
#include "Edge.h"
#include "set"

class WeightedGraph{
    std::vector<Edge> edges;
    std::vector<std::vector<std::pair<int, double>>> vertices;
    int edgesCnt;
    double getWeight(int from, int to);
public:
    WeightedGraph(int vertCnt, int numEdges): vertices(vertCnt), edges(numEdges), edgesCnt(0){};
    WeightedGraph(int vertCnt) : vertices(vertCnt), edgesCnt(0){};
    void setEdgesCnt(int edgesCnt_);
    void addEdge(int vert1, int vert2, double weight);
    size_t getSize() const {return vertices.size();}
    size_t edgeCount() const {return edgesCnt;}
    std::vector<Edge> getEdges(){return edges;}
    double kruskal();
    double bruteForce();
    WeightedGraph operator = (WeightedGraph graph);
};


#endif //DZ3_WEIGHTEDGRAPH_H
