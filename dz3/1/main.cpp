//
// Created by Марат Гасанов on 24.05.2022.
//
#include "AdjancyList.h"
#include "AdjancyMatrix.h"
#include "ArcGraph.h"
#include "SetGraph.h"
#include <cassert>
#include "set"

bool isVectorEqual(std::vector<int> vec1, std::vector<int> vec2){
    std::set<int> set1(vec1.begin(), vec1.end());
    std::set<int> set2(vec2.begin(), vec2.end());
    return set1 == set2;
}

void test(IGraph* graph){
    int commandType, vertexFrom, vertexTo, vertex;
    std::vector<int> vert1 = {0, 0, 1, 1, 2, 2, 2};
    std::vector<int> vert2 = {2, 1, 2, 5, 4, 3, 0};
    std::vector<int> vertoxGetPrev = {0, 2};
    std::vector<std::vector<int>> vertoxGetPrevTest = {{2}, {0,1}};
    std::vector<int> vertoxGetNext = {1, 2};
    std::vector<std::vector<int>> vertoxGetNextTest = {{2, 5}, {0, 3, 4}};

    for (int i = 0; i< vert1.size(); i++){
        vertexFrom = vert1[i];
        vertexTo = vert2[i];
        graph->AddEdge(vertexFrom, vertexTo);
    }

    for (int i = 0; i < vertoxGetPrev.size(); ++i) {
        std::vector<int> prev = graph->GetPrevVertices(vertoxGetPrev[i]);
        assert(isVectorEqual(prev, vertoxGetPrevTest[i]));
    }

    for (int i = 0; i < vertoxGetNext.size(); ++i) {
        std::vector<int> next = graph->GetNextVertices(vertoxGetNext[i]);
        assert(isVectorEqual(next, vertoxGetNextTest[i]));
    }
}


int main(){
    IGraph* adjList = new AdjancyListGraph(6);
    IGraph* adjMatrix = new AdjancyMatrix(6);
    IGraph* arcGraph = new ArcGraph(6);
    IGraph* setGraph = new SetGraph(6);
    test(adjList);
    test(adjMatrix);
    test(arcGraph);
    test(setGraph);
}
