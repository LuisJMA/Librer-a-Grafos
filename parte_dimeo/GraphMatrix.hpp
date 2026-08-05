#ifndef GRAPH_MATRIX_HPP 
#define GRAPH_MATRIX_HPP 
 
#include "CustomVector.hpp" 
#include <iostream> 
 
namespace SimpleGraph { 
    template <typename T> 
    class GraphMatrix { 
    private: 
        CustomVector<T> vertices; 
        CustomVector<CustomVector<double>> matrix; 
        bool isDirected; 
 
        int getVertexIndex(const T& vertex) const; 
    };
}