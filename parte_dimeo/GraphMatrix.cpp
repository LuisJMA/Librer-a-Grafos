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
 