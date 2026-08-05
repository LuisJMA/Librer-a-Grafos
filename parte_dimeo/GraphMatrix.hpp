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

        public: 
        GraphMatrix(bool directed = false); 
        void addVertex(const T& vertex); 
        void addEdge(const T& source, const T& destination, double weight = 1.0); 
    };

}

#include "../src/GraphMatrix.cpp" 
#endif