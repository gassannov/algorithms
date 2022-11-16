//
// Created by Марат Гасанов on 29.05.2022.
//
#include "WeightedGraph.h"
void WeightedGraph::addEdge(int vert1, int vert2, double weight) {
    vertices[vert1].push_back({vert2, weight});
    vertices[vert2].push_back({vert1, weight});
    edges[edgesCnt] = {vert1, vert2, weight};
    edgesCnt++;
}

double WeightedGraph::kruskal() {
    int size = getSize();
    std::vector<int> groups(size);
    double minimalWeight = 0;
    for (int i = 0; i < size; ++i) {
        groups[i] = i;
    }
    int i = 0;
    std::sort(edges.begin(), edges.end());
    for (Edge minEdge: edges){
        int vert1 = minEdge.startVertex;
        int vert2 = minEdge.endVertex;
        if (groups[vert1] != groups[vert2]){
            int newGroup = groups[vert1];
            int oldGroup = groups[vert2];
            i++;
            minimalWeight += minEdge.length;
            for (int i = 0; i < size; ++i) {
                if (groups[i] == oldGroup){
                    groups[i] = newGroup;
                }
            }
        }
    }
    return minimalWeight;
}

double WeightedGraph::bruteForce() {
    int verticesCount = getSize();
    std::vector<int> verts;
    for (int i = 0; i < verticesCount; i++) {
        verts.push_back(i);
    }

    std::vector<double> weights;
    do {
        double weight = 0;
        double edgeWeight = 0;
        for (int i = 0; i < verticesCount-1; i++) {
            edgeWeight = getWeight(verts[i], verts[i + 1]);
            if (edgeWeight != -1) {
                weight += edgeWeight;
            }
        }

        weights.push_back(weight);
    } while (std::next_permutation(verts.begin(), verts.end()));

    return *std::min_element(weights.begin(), weights.end());
    return 0;
}

double WeightedGraph::getWeight(int from, int to) {
    if (from > getSize() || to > getSize()) return -1;
    for (int i = 0; i < vertices[from].size(); ++i) {
        if (vertices[from][i].first == to){
            return vertices[from][i].second;
        }
    }
    return -1;
}

WeightedGraph WeightedGraph::operator=(WeightedGraph graph) {
    graph.vertices = this->vertices;
    graph.edges = this->edges;
    return graph;
}

void WeightedGraph::setEdgesCnt(int edgesCnt_) {
    std::vector<Edge> newEdges(edgesCnt_);
    edges = newEdges;
}
