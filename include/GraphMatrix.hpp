#ifndef GRAPH_MATRIX_HPP 
#define GRAPH_MATRIX_HPP 
 
#include "AbstractGraph.hpp" 
#include "CustomVector.hpp" 
#include "CustomQueue.hpp" 
#include <iostream> 
#include <limits> 
 
namespace SimpleGraph { 
    template <typename T> 
    class GraphMatrix : public AbstractGraph<T> { 
    private: 
        CustomVector<T> vertices; 
        CustomVector<CustomVector<double>> matrix; 
        bool isDirected; 
 
        int getVertexIndex(const T& vertex) const; 
        void DFSHelper(int vertexIdx, CustomVector<bool>& visited, CustomVector<T>& result); 
 
    public: 
        GraphMatrix(bool directed = false); 
 
        void addVertex(const T& vertex) override; 
        void addEdge(const T& source, const T& destination, double weight = 1.0) override; 
        void removeEdge(const T& source, const T& destination) override; 
        bool hasEdge(const T& source, const T& destination) const override; 
        void printGraph() const override; 
 
        CustomVector<T> BFS(const T& startVertex) override; 
        CustomVector<T> DFS(const T& startVertex) override; 
        PathResult<T> shortestPathDijkstra(const T& startVertex, const T& endVertex) override; 
    }; 
} 
 
#include "../src/GraphMatrix.cpp" 
#endif