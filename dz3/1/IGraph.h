//
// Created by Марат Гасанов on 24.05.2022.
//
#ifndef DZ3_IGRAPH_H
#define DZ3_IGRAPH_H
struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
#endif
