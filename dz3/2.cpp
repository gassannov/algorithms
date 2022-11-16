//
// Created by Марат Гасанов on 24.05.2022.
//

#include "iostream"
#include "vector"
#include "queue"

class CityGraph{
    std::vector<std::vector<int>> matrix;
public:
    explicit CityGraph(int vertCnt): matrix(vertCnt){};
    std::vector<int> getVertexes (int vertId) const;
    void addEdge(int vert1, int vert2);
    size_t getSize() const {return matrix.size();}
};

std::vector<int> CityGraph::getVertexes(int vertId) const{
    return matrix[vertId];
}

void CityGraph::addEdge(int vert1, int vert2) {
    matrix[vert1].push_back(vert2);
    matrix[vert2].push_back(vert1);
}

int minCount(const CityGraph& graph, int from, int to){
    std::queue<int> current;
    current.push(from);
    std::vector<int> lengths(graph.getSize(), 10000*10000);
    std::vector<int> countMin(graph.getSize(), 0);
    lengths[from] = 0;
    countMin[from] = 1;
    while (!current.empty()){
        std::queue<int> nextCurrent;
        while (!current.empty()){
            int currVert = current.front();
            current.pop();
            std::vector<int> currVertVertex = graph.getVertexes(currVert);
            for (int i = 0; i < currVertVertex.size(); ++i) {
                if (lengths[currVert] + 1 < lengths[currVertVertex[i]]){
                    lengths[currVertVertex[i]] = lengths[currVert] + 1;
                    nextCurrent.push(currVertVertex[i]);
                }
                if (lengths[currVertVertex[i]] == lengths[currVert] + 1){
                    countMin[currVertVertex[i]] += countMin[currVert];
                }
            }
        }
        current = nextCurrent;
    }
    return countMin[to];
}

int main(){
    int numVertex, numEdges, from, to;
    std::cin >> numVertex;
    std::cin >> numEdges;
    CityGraph graph(numVertex);
    for (int i = 0; i < numEdges; ++i) {
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }
    std::cin >> from >> to;
    std::cout << minCount(graph, from, to) << std::endl;
};