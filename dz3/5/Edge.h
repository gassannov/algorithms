//
// Created by Марат Гасанов on 29.05.2022.
//

#ifndef DZ3_EDGE_H
#define DZ3_EDGE_H


struct Edge{
    int startVertex;
    int endVertex;
    double length;
    bool operator >(const Edge& node) const {return length > node.length;}
    bool operator <(const Edge& node) const {return length < node.length;}
};


#endif //DZ3_EDGE_H
