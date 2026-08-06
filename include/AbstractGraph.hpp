#ifndef ABSTRACT_GRAPH_HPP
#define ABSTRACT_GRAPH_HPP

#include "CustomVector.hpp"

namespace SimpleGraph {
    #ifndef PATH_RESULT_STRUCT
    #define PATH_RESULT_STRUCT
    template <typename T>
    struct PathResult {
        CustomVector<T> path;
        double totalDistance;
    };
    #endif

    template <typename T>
    class AbstractGraph {
    public:
        virtual ~AbstractGraph() = default;

        virtual void addVertex(const T& vertex) = 0;
        virtual void addEdge(const T& source, const T& destination, double weight = 1.0) = 0;
        virtual void removeEdge(const T& source, const T& destination) = 0;
        virtual bool hasEdge(const T& source, const T& destination) const = 0;
        virtual void printGraph() const = 0;

        virtual CustomVector<T> BFS(const T& startVertex) = 0;
        virtual CustomVector<T> DFS(const T& startVertex) = 0;
        virtual PathResult<T> shortestPathDijkstra(const T& startVertex, const T& endVertex) = 0;
    };
}

#endif