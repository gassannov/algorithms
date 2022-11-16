//
// Created by Марат Гасанов on 24.05.2022.
//

#include "AdjancyList.h"

std::vector<int> AdjancyListGraph::GetPrevVertices(int vertex) const{
    std::vector<int> prevVertices;
    for (int i = 0; i < vertexes.size(); ++i) {
        for (int j = 0; j < vertexes[i].size(); ++j) {
            if (vertexes[i][j] == vertex)
                prevVertices.push_back(i);
        }
    }
    return prevVertices;
}

void AdjancyListGraph::AddEdge(int from, int to) {
    vertexes[from].push_back(to);
}

std::vector<int> AdjancyListGraph::GetNextVertices(int vertex) const{
    return vertexes[vertex];
}

AdjancyListGraph::~AdjancyListGraph() {

}

void AdjancyListGraph::buildBromIGRaph(const IGraph &graph) {
    std::vector<std::vector<int>> newVertexes(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        newVertexes[i] = graph.GetNextVertices(i);
    }
    vertexes = newVertexes;
}
