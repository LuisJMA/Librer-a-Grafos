#ifndef GRAPH_LIST_HPP
#define GRAPH_LIST_HPP

#include "CustomVector.hpp"
#include "CustomQueue.hpp"
#include <iostream>
#include <limits>

namespace SimpleGraph {
    template <typename T>
    struct PathResult {
        CustomVector<T> path;
        double totalDistance;
    };

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
        PathResult<T> shortestPathDijkstra(const T& startVertex, const T& endVertex);
    };
}

#include "../src/GraphList.cpp"
#endif