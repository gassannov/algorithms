//
// Created by Марат Гасанов on 3.06.2022.
//

#include "iostream"
#include "vector"
#include "queue"
//#include "1/ArcGraph.h"
#include "assert.h"
#include "set"
using namespace std;

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
}

bool Relax(std::vector<int>& d, int const u, int const & v, int dB){
    if(d[v] > d[u] + dB){
        d[v] = d[u] + dB;
        return true;
    }
    return false;
}


int Dijkstra( const CityGraph graph, int s, int w) {
    std::vector<int> d = std::vector<int>(graph.getSize(),0x7fffffff);
    d[s] = 0;
    set<pair<int, int>> q; q.insert(make_pair(0, s) ); // distance, vertex
    while( !q.empty() ) {
        pair<int, int> p = *(q.begin());
        q.erase(q.begin());
        int u = p.second;
        for( auto r : graph.getVertexes(u) ) {
            if( d[r.first] == 0x7fffffff ) {
                d[r.first] = d[u] + r.second;
                q.insert(make_pair(d[r.first] ,r.first) );
            } else if(Relax( d, u, r.first, r.second )) {
                for(auto i = q.begin(); i != q.end(); i++){
                    if(i->second == r.first){
                        q.erase(i);
                        break;
                    }
                }
                q.insert(make_pair(d[r.first] ,r.first) );
            }
        }
    }
    return d[w];
}


int main(){
    int a, b, M, from, to;
    std::cin >> a >> b >> M >> from >> to;
    CityGraph cityGraph(M);
    for (int i = 0; i < M; ++i) {
        int z1 = ((i+1) % M);
        int z2 = ((i*i+1) % M);
        cityGraph.addEdge(i, z1, a);
        cityGraph.addEdge(i, z2, b);
    }
    std::cout << Dijkstra(cityGraph, from, to) << std::endl;
};