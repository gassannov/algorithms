//
// Created by Марат Гасанов on 24.05.2022.
//

#include "AdjancyMatrix.h"

void AdjancyMatrix::AddEdge(int from, int to) {
    matrix[from][to]++;
}

int AdjancyMatrix::VerticesCount() const {
    return size;
}

std::vector<int> AdjancyMatrix::GetNextVertices(int vertex) const {
    std::vector<int> nums;
    for (int i = 0; i < matrix[vertex].size(); ++i) {
        if (matrix[vertex][i] > 0){
            nums.push_back(i);
        }
    }
    return nums;
}

std::vector<int> AdjancyMatrix::GetPrevVertices(int vertex) const {
    std::vector<int> nums;
    for (int i = 0; i < size; ++i) {
        if(matrix[i][vertex] > 0){
            nums.push_back(i);
        }
    }
    return nums;
}

AdjancyMatrix::AdjancyMatrix(int vertCnt) {
    std::vector<int> zeros;
    for (int i = 0; i < vertCnt; ++i) {
        zeros.push_back(0);
    }
    for (int i = 0; i < vertCnt; ++i) {
        matrix.push_back(zeros);
    }
    size = vertCnt;
}

void AdjancyMatrix::buildfromIGraph(const IGraph &graph) {
    if (graph.VerticesCount() != this->VerticesCount()) return;
    std::vector<int> nextVertices;
    int k;
    for (int i = 0; i < this->VerticesCount(); ++i) {
        nextVertices = graph.GetNextVertices(i);
        for (int j = 0; j < this->VerticesCount(); ++j) {
            if (std::find(nextVertices.begin(), nextVertices.end(), j) != nextVertices.end()){
                matrix[i][j] = 1;
            }
            else{
                matrix[i][j] = 0;
            }
        }
    }
}
