#include "SetGraph.h"

SetGraph::SetGraph(int vertCount){
    vertexes.resize(vertCount);
}

SetGraph::SetGraph(const IGraph & graph){
    vertexes.resize(graph.VerticesCount());
    for(int from = 0; from < graph.VerticesCount(); ++from){
        auto children = graph.GetNextVertices(from);
        for(auto const & to : children){
            this->AddEdge(from, to);
        }
    }
}

void SetGraph::AddEdge(int from, int to){
    vertexes[from].insert(to);
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    std::vector<int> result = std::vector<int>(vertexes[vertex].begin(), vertexes[vertex].end());
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (int from = 0; from < vertexes.size(); ++from)
    {
        if (from == vertex)
            continue;
        for (auto const &i : vertexes[from])
        {
            if (vertex == i)
            {
                result.push_back(from);
                break;
            }
        }
    }
    return result;
}

SetGraph::~SetGraph() {

}
