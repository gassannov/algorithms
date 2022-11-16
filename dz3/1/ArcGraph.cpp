//
// Created by Марат Гасанов on 24.05.2022.
//

#include "ArcGraph.h"

void ArcGraph::AddEdge(int from, int to) {
    std::pair<int, int> pair = {from, to};
    pairs.push_back(pair);
}

int ArcGraph::VerticesCount() const {
    std::set<int> verts;
    for (int i = 0; i < pairs.size(); ++i) {
        verts.insert(pairs[i].first);
        verts.insert(pairs[i].second);
    }
    return verts.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> nexts;
    for (int i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first == vertex){
            nexts.push_back(pairs[i].second);
        }
    }
    return nexts;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> nexts;
    for (int i = 0; i < pairs.size(); ++i) {
        if (pairs[i].second == vertex){
            nexts.push_back(pairs[i].first);
        }
    }
    return nexts;
}

ArcGraph::ArcGraph(const IGraph & graph) {
    this->vertCnt = graph.VerticesCount();
    for(int from = 0; from < vertCnt; ++from){
        auto children = graph.GetNextVertices(from);
        for(auto const & to : children){
            this->AddEdge(from, to);
        }
    }
}
