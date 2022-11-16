//
// Created by Марат Гасанов on 3.06.2022.
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

bool isAllVisited(std::vector<int> arr){
    for (int i: arr) {
        if (!i) return false;
    }
    return true;
}

void dfs(CityGraph graph, std::vector<int>& visited, int vertex){
    visited[vertex] = true;
    std::queue<int> que;
    que.push(vertex);
    while (!que.empty()){
        int v = que.front();
        que.pop();
        visited[v] = true;
        for (int nextV: graph.getVertexes(v)) {
            if (!visited[nextV])
                que.push(nextV);
        }
    }
}

int componentCnt(CityGraph graph){
    int verCnt = graph.getSize();
    int compCnt = 0;
    std::vector<int> visited(verCnt, 0);
    for (int i = 0; i < verCnt; ++i) {
        if (visited[i] == 0){
            dfs(graph, visited, i);
            compCnt++;
        }
    }
    return compCnt;
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
    std::cout << componentCnt(graph) << std::endl;
};