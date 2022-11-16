//
// Created by Марат Гасанов on 03.06.2022.
//

#include <stack>
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"

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

bool isWayHamilton(CityGraph graph, std::vector<int> way){
    std::vector<int> isVPassed(graph.getSize(), 0);
    if (way.size() != graph.getSize()) return false;
    for (int i = 0; i < way.size(); ++i) {
        if (isVPassed[way[i]]) return false;
        isVPassed[way[i]] = true;
    }
    return true;
}

bool isHamiltonPossible(CityGraph graph){
    for (int i = 0; i < graph.getSize(); ++i) {
        if (graph.getVertexes(i).size() < graph.getSize()/2){
            return false;
        }
    }
    return true;
}

bool isHamiltonWay(const CityGraph graph, std::queue<int> q){
    std::vector<bool> visited(graph.getSize(), 0);
    std::stack<int> stack;
    stack.push(q.front()); q.pop();
    while (!stack.empty())
    {
        int cur = stack.top();
        stack.pop();
        if (!visited[cur])
        {
            visited[cur] = true;
        }
        auto const & children = graph.getVertexes(cur);
        int next_v = q.front(); q.pop();
        if(std::find(children.begin(), children.end(), next_v) != children.end()){
            if(!visited[next_v]){
                stack.push(next_v);
            }
        } else {
            return false;
        }
    }
    for(int edg = 0; edg < graph.getSize(); ++edg){
        if(!visited[edg]){
            return  false;
        }
    }
    return true;
}

int main(){
    int numVertex, numEdges,numWay, from, to;
    std::cin >> numVertex;
    std::cin >> numEdges;
    std::cin >> numWay;
    CityGraph graph(numVertex);
    for (int i = 0; i < numEdges; ++i) {
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }
    std::queue<int> way;
    for (int i = 0; i < numWay; ++i) {
        int num;
        std::cin >> num;
        way.push(num);
    }
    std::cout << isHamiltonWay(graph, way) << std::endl;
}
