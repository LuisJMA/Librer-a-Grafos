#ifndef GRAPH_LIST_HPP
#define GRAPH_LIST_HPP

#include "CustomVector.hpp"
#include "CustomQueue.hpp"
#include <iostream>

namespace SimpleGraph {
    template <typename T>
    class GraphList {
    private:
        struct Edge {
            int destIndex;
            double weight;
        };

        CustomVector<T> vertices;
        CustomVector<CustomVector<Edge>> adjList;
        bool isDirected;

        int getVertexIndex(const T& vertex) const;

    public:
        GraphList(bool directed = false);
        void addVertex(const T& vertex);
        void addEdge(const T& source, const T& destination, double weight = 1.0);
        CustomVector<T> BFS(const T& startVertex);
        void shortestPathDijkstra(const T& startVertex);
    };
}

#include "../src/GraphList.cpp"
#endif