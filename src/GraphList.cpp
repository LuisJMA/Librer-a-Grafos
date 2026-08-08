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
    bool GraphList<T>::hasEdge(const T& source, const T& destination) const {
        int srcIdx = getVertexIndex(source);
        int destIdx = getVertexIndex(destination);
        if (srcIdx == -1 || destIdx == -1) return false;

        for (int i = 0; i < adjList.at(srcIdx).size(); i++) {
            if (adjList.at(srcIdx).at(i).destIndex == destIdx) return true;
        }
        return false;
    }

    template <typename T>
    void GraphList<T>::removeEdge(const T& source, const T& destination) {
        int srcIdx = getVertexIndex(source);
        int destIdx = getVertexIndex(destination);
        if (srcIdx == -1 || destIdx == -1) return;

        for (int i = 0; i < adjList.at(srcIdx).size(); i++) {
            if (adjList.at(srcIdx).at(i).destIndex == destIdx) {
                adjList.at(srcIdx).removeAt(i);
                break;
            }
        }

        if (!isDirected) {
            for (int i = 0; i < adjList.at(destIdx).size(); i++) {
                if (adjList.at(destIdx).at(i).destIndex == srcIdx) {
                    adjList.at(destIdx).removeAt(i);
                    break;
                }
            }
        }
    }

    template <typename T>
    void GraphList<T>::printGraph() const {
        std::cout << "\n--- LISTA DE ADYACENCIA ---\n";
        for (int i = 0; i < vertices.size(); i++) {
            std::cout << vertices.at(i) << " -> ";
            for (int j = 0; j < adjList.at(i).size(); j++) {
                int destIdx = adjList.at(i).at(j).destIndex;
                double w = adjList.at(i).at(j).weight;
                std::cout << "[" << vertices.at(destIdx) << " | Peso: " << w << "] ";
            }
            std::cout << "\n";
        }
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
    void GraphList<T>::DFSHelper(int vertexIdx, CustomVector<bool>& visited, CustomVector<T>& result) {
        visited.at(vertexIdx) = true;
        result.push_back(vertices.at(vertexIdx));

        for (int i = 0; i < adjList.at(vertexIdx).size(); i++) {
            int neighborIdx = adjList.at(vertexIdx).at(i).destIndex;
            if (!visited.at(neighborIdx)) {
                DFSHelper(neighborIdx, visited, result);
            }
        }
    }

    template <typename T>
    CustomVector<T> GraphList<T>::DFS(const T& startVertex) {
        int startIdx = getVertexIndex(startVertex);
        if (startIdx == -1) throw std::invalid_argument("El vertice no existe.");

        CustomVector<T> result;
        CustomVector<bool> visited;
        visited.resize(vertices.size(), false);

        DFSHelper(startIdx, visited, result);
        return result;
    }

    template <typename T>
    PathResult<T> GraphList<T>::shortestPathDijkstra(const T& startVertex, const T& endVertex) {
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

            for (int j = 0; j < adjList.at(minIdx).size(); j++) {
                int neighbor = adjList.at(minIdx).at(j).destIndex;
                double weight = adjList.at(minIdx).at(j).weight;
                if (!visited.at(neighbor) && dist.at(minIdx) + weight < dist.at(neighbor)) {
                    dist.at(neighbor) = dist.at(minIdx) + weight;
                    parent.at(neighbor) = minIdx;
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
#endif