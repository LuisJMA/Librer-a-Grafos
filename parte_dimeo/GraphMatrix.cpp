#ifndef GRAPH_MATRIX_CPP 
#define GRAPH_MATRIX_CPP 
 
#include "../parte_dimeo/GraphMatrix.hpp" 
 
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
            vertices.push_back(vertex); 
            int newSize = vertices.size(); 
             
            for (int i = 0; i < matrix.size(); i++) { 
                matrix.at(i).push_back(999999.0); 
            } 
             
            CustomVector<double> newRow; 
            newRow.resize(newSize, 999999.0); 
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
} 
#endif 