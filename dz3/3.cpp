//
// Created by Марат Гасанов on 24.05.2022.
//

#include "iostream"
#include "vector"
#include "queue"
//#include "1/ArcGraph.h"
#include "assert.h"

class CityGraph{
    std::vector<std::vector<std::pair<int, int>>> matrix;
public:
    explicit CityGraph(int vertCnt): matrix(vertCnt){};
    std::vector<std::pair<int, int>> getVertexes (int vertId) const;
    void addEdge(int vert1, int vert2, int weight);
    size_t getSize() const {return matrix.size();}
};

std::vector<std::pair<int, int>> CityGraph::getVertexes(int vertId) const{
    return matrix[vertId];
}

void CityGraph::addEdge(int vert1, int vert2, int weight) {
    matrix[vert1].push_back({vert2, weight});
    matrix[vert2].push_back({vert1, weight});
}

int numShortest(const CityGraph& graph, int from, int to){
    /*Алгоритм нахождения
     * добавляем вершину "from" в очередь расстояние до нее равно нулю
     * вытаскиваем ее из очереди
     * все смежные вершины добавляем в очередь и помечаем и помечаем их расстояние
     * проделываем тоже самое со всеми элементами очереди
     * когда очередь опустеет выходим из цикла
     * продолжаем пока очередь не окажется пустой
     * в следующий шагах добавляем элемент в очередь только если его расстояние было изменено
     */
    std::queue<int> current;
    current.push(from);
    std::vector<int> lengths(graph.getSize(), 10000*10000);
    lengths[from] = 0;
    while (!current.empty()){
        std::queue<int> nextCurrent;
        while (!current.empty()){
            int currVert = current.front();
            current.pop();
            std::vector<std::pair<int, int>> currVertVertex = graph.getVertexes(currVert);
            for (int i = 0; i < currVertVertex.size(); ++i) {
                if (lengths[currVert] + currVertVertex[i].second < lengths[currVertVertex[i].first]){
                    nextCurrent.push(currVertVertex[i].first);
                    lengths[currVertVertex[i].first] = lengths[currVert] + currVertVertex[i].second;
                }
            }
        }
        current = nextCurrent;
    }
    return lengths[to];
}

int main(){
    int numVertex, numEdges, from, to, length;
    std::cin >> numVertex;
    std::cin >> numEdges;
    CityGraph graph(numVertex);
    for (int i = 0; i < numEdges; ++i) {
        std::cin >> from >> to >> length;
        graph.addEdge(from, to, length);
    }
    std::cin >> from >> to;
    std::cout << numShortest(graph, from, to) << std::endl;
};