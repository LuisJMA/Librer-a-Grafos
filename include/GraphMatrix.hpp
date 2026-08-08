#ifndef GRAPH_MATRIX_HPP 
#define GRAPH_MATRIX_HPP 
 
#include "CustomVector.hpp" 
#include "CustomQueue.hpp" 
#include <iostream> 
#include <limits> 
 
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
    class GraphMatrix { 
    private: 
        CustomVector<T> vertices; 
        CustomVector<CustomVector<double>> matrix; 
        bool isDirected; 
 
        int getVertexIndex(const T& vertex) const; 
 
    public: 
        GraphMatrix(bool directed = false); 
        void addVertex(const T& vertex); 
        void addEdge(const T& source, const T& destination, double weight = 1.0); 
        CustomVector<T> BFS(const T& startVertex); 
        PathResult<T> shortestPathDijkstra(const T& startVertex, const T& endVertex); 
    }; 
} 
 
#include "../src/GraphMatrix.cpp" 
#endif