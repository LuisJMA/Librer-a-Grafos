#ifndef GRAPH_MATR IX_CPP
#define GRAPH_MATRIX_CPP 
 
#include "parte_dimeo/GraphMatrix.hpp" 
 
namespace SimpleGraph { 
    template <typename T> 
    GraphMatrix<T>::GraphMatrix(bool directed) : isDirected(directed) {} 
 
    template <typename T> 
    int GraphMatrix<T>::getVertexIndex(const T& vertex) const { 
        for (int i = 0; i < vertices.size(); i++) { 
            if (vertices.at(i) == vertex) return i; 
        } 
        return -1; 
    } 
 
    template <typename T> 
    void GraphMatrix<T>::addVertex(const T& vertex) { 
        if (getVertexIndex(vertex) == -1) { 
            double INF = std::numeric_limits<double>::infinity(); 
            vertices.push_back(vertex); 
            int newSize = vertices.size(); 
             
            for (int i = 0; i < matrix.size(); i++) { 
                matrix.at(i).push_back(INF); 
            } 
             
            CustomVector<double> newRow; 
            newRow.resize(newSize, INF); 
            matrix.push_back(newRow); 
        } 
    } 
 
    template <typename T> 
    void GraphMatrix<T>::addEdge(const T& source, const T& destination, double weight) { 
        addVertex(source); 
        addVertex(destination); 
 
        int srcIdx = getVertexIndex(source); 
        int destIdx = getVertexIndex(destination); 
 
        matrix.at(srcIdx).at(destIdx) = weight; 
        if (!isDirected) { 
            matrix.at(destIdx).at(srcIdx) = weight; 
        } 
    } 
 
    template <typename T> 
    CustomVector<T> GraphMatrix<T>::BFS(const T& startVertex) { 
        int startIdx = getVertexIndex(startVertex); 
        if (startIdx == -1) throw std::invalid_argument("El vertice no existe."); 
 
        double INF = std::numeric_limits<double>::infinity(); 
        CustomVector<T> result; 
        CustomVector<bool> visited; 
        visited.resize(vertices.size(), false); 
        CustomQueue<int> q; 
 
        q.push(startIdx); 
        visited.at(startIdx) = true; 
 
        while (!q.isEmpty()) { 
            int current = q.front(); 
            q.pop(); 
            result.push_back(vertices.at(current)); 
 
            for (int j = 0; j < vertices.size(); j++) { 
                if (matrix.at(current).at(j) < INF && !visited.at(j)) { 
                    visited.at(j) = true; 
                    q.push(j); 
                } 
            } 
        } 
        return result; 
    } 
 
    template <typename T> 
    PathResult<T> GraphMatrix<T>::shortestPathDijkstra(const T& startVertex, const T& endVertex) { 
        int startIdx = getVertexIndex(startVertex); 
        int endIdx = getVertexIndex(endVertex); 
 
        if (startIdx == -1 || endIdx == -1) { 
            throw std::invalid_argument("Vertice de origen o destino inexistente."); 
        } 
 
        int n = vertices.size(); 
        double INF = std::numeric_limits<double>::infinity(); 
        CustomVector<double> dist; 
        CustomVector<bool> visited; 
        CustomVector<int> parent; 
 
        dist.resize(n, INF); 
        visited.resize(n, false); 
        parent.resize(n, -1); 
 
        dist.at(startIdx) = 0.0; 
 
        for (int i = 0; i < n - 1; i++) { 
            double minDist = INF; 
            int minIdx = -1; 
            for (int v = 0; v < n; v++) { 
                if (!visited.at(v) && dist.at(v) <= minDist) { 
                    minDist = dist.at(v); 
                    minIdx = v; 
                } 
            } 
            if (minIdx == -1) break; 
            visited.at(minIdx) = true; 
 
            for (int j = 0; j < n; j++) { 
                double weight = matrix.at(minIdx).at(j); 
                if (weight < INF && !visited.at(j)) { 
                    if (dist.at(minIdx) + weight < dist.at(j)) { 
                        dist.at(j) = dist.at(minIdx) + weight; 
                        parent.at(j) = minIdx; 
                    } 
                } 
            } 
        } 
 
        PathResult<T> result; 
        result.totalDistance = dist.at(endIdx); 
 
        if (dist.at(endIdx) == INF) return result;
         CustomVector<T> reversePath; 
        int curr = endIdx; 
        while (curr != -1) { 
            reversePath.push_back(vertices.at(curr)); 
            curr = parent.at(curr); 
        } 
 
        for (int i = reversePath.size() - 1; i >= 0; i--) { 
            result.path.push_back(reversePath.at(i)); 
        } 
 
        return result; 
    } 
} 

#endif GRAPH_MATR IX_CPP