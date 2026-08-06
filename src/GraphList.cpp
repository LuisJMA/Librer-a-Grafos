#ifndef GRAPH_LIST_CPP
#define GRAPH_LIST_CPP

#include "../include/GraphList.hpp"

namespace SimpleGraph {
    template <typename T>
    GraphList<T>::GraphList(bool directed) : isDirected(directed) {}

    template <typename T>
    int GraphList<T>::getVertexIndex(const T& vertex) const {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i) == vertex) return i;
        }
        return -1;
    }

    template <typename T>
    void GraphList<T>::addVertex(const T& vertex) {
        if (getVertexIndex(vertex) == -1) {
            vertices.push_back(vertex);
            CustomVector<Edge> emptyList;
            adjList.push_back(emptyList);
        }
    }

    template <typename T>
    void GraphList<T>::addEdge(const T& source, const T& destination, double weight) {
        addVertex(source);
        addVertex(destination);

        int srcIdx = getVertexIndex(source);
        int destIdx = getVertexIndex(destination);

        adjList.at(srcIdx).push_back({destIdx, weight});
        if (!isDirected) adjList.at(destIdx).push_back({srcIdx, weight});
    }

    template <typename T>
    CustomVector<T> GraphList<T>::BFS(const T& startVertex) {
        int startIdx = getVertexIndex(startVertex);
        if (startIdx == -1) throw std::invalid_argument("El vertice no existe.");

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

            for (int i = 0; i < adjList.at(current).size(); i++) {
                int neighborIdx = adjList.at(current).at(i).destIndex;
                if (!visited.at(neighborIdx)) {
                    visited.at(neighborIdx) = true;
                    q.push(neighborIdx);
                }
            }
        }
        return result;
    }

    template <typename T>
    void GraphList<T>::shortestPathDijkstra(const T& startVertex) {
        int startIdx = getVertexIndex(startVertex);
        if (startIdx == -1) throw std::invalid_argument("El vertice no existe.");

        int n = vertices.size();
        CustomVector<double> dist;
        CustomVector<bool> visited;
        dist.resize(n, 999999.0);
        visited.resize(n, false);

        dist.at(startIdx) = 0.0;

        for (int i = 0; i < n - 1; i++) {
            double minDist = 999999.0;
            int minIdx = -1;
            for (int v = 0; v < n; v++) {
                if (!visited.at(v) && dist.at(v) <= minDist) {
                    minDist = dist.at(v);
                    minIdx = v;
                }
            }
            if (minIdx == -1) break;
            visited.at(minIdx) = true;

            for (int j = 0; j < adjList.at(minIdx).size(); j++) {
                int neighbor = adjList.at(minIdx).at(j).destIndex;
                double weight = adjList.at(minIdx).at(j).weight;
                if (!visited.at(neighbor) && dist.at(minIdx) + weight < dist.at(neighbor)) {
                    dist.at(neighbor) = dist.at(minIdx) + weight;
                }
            }
        }

        std::cout << "\nDistancias Dijkstra desde " << startVertex << ":\n";
        for (int i = 0; i < n; i++) {
            std::cout << vertices.at(i) << " -> " << dist.at(i) << "\n";
        }
    }
}
#endif