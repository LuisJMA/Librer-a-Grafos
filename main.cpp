#include <iostream>
#include <string>
#include <limits>
#include "include/AbstractGraph.hpp"
#include "include/GraphList.hpp"
#include "include/GraphMatrix.hpp"

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void cargarGrafoDePrueba(SimpleGraph::AbstractGraph<std::string>* graph) {
    graph->addEdge("Caracas", "Maracay", 80.0);
    graph->addEdge("Maracay", "Valencia", 50.0);
    graph->addEdge("Caracas", "Valencia", 150.0);
    graph->addEdge("Valencia", "Barquisimeto", 180.0);
    graph->addEdge("Maracay", "Barquisimeto", 200.0);
    graph->addEdge("Barquisimeto", "Maracaibo", 320.0);
    std::cout << "\n[+] Grafo de prueba precargado exitosamente (6 ciudades y 6 conexiones).\n";
}

void menuPolimorfico(SimpleGraph::AbstractGraph<std::string>* graph, const std::string& nombreEstructura) {
    int option = 0;

    do {
        std::cout << "\n==========================================\n";
        std::cout << "   GESTOR DE GRAFO: " << nombreEstructura << "\n";
        std::cout << "==========================================\n";
        std::cout << "1. Agregar Vertice (Nodo)\n";
        std::cout << "2. Agregar Arista (Conexion con Peso)\n";
        std::cout << "3. Eliminar Arista\n";
        std::cout << "4. Verificar si existe Arista (hasEdge)\n";
        std::cout << "5. Visualizar Grafo (printGraph)\n";
        std::cout << "6. Ejecutar Recorrido BFS (Amplitud)\n";
        std::cout << "7. Ejecutar Recorrido DFS (Profundidad)\n";
        std::cout << "8. Camino Mas Corto (Dijkstra con Ruta)\n";
        std::cout << "9. Precargar Grafo de Prueba (Auto-Poblar)\n";
        std::cout << "10. Volver al Menu Principal\n";
        std::cout << "Opcion: ";

        if (!(std::cin >> option)) {
            std::cout << "\n[!] Entrada invalida. Ingrese un numero.\n";
            clearBuffer();
            continue;
        }

        switch (option) {
            case 1: {
                std::string vertex;
                std::cout << "Nombre del vertice: ";
                std::cin >> vertex;
                try {
                    graph->addVertex(vertex);
                    std::cout << "[+] Vertice '" << vertex << "' agregado con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "[X] Error: " << e.what() << "\n";
                }
                break;
            }
            case 2: {
                std::string src, dest;
                double weight;
                std::cout << "Vertice Origen: ";
                std::cin >> src;
                std::cout << "Vertice Destino: ";
                std::cin >> dest;
                std::cout << "Peso de la arista: ";
                if (!(std::cin >> weight)) {
                    std::cout << "[!] Peso invalido.\n";
                    clearBuffer();
                    break;
                }
                try {
                    graph->addEdge(src, dest, weight);
                    std::cout << "[+] Arista (" << src << " -> " << dest << " | Peso: " << weight << ") agregada.\n";
                } catch (const std::exception& e) {
                    std::cout << "[X] Error: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                std::string src, dest;
                std::cout << "Vertice Origen: ";
                std::cin >> src;
                std::cout << "Vertice Destino: ";
                std::cin >> dest;
                try {
                    graph->removeEdge(src, dest);
                    std::cout << "[-] Arista eliminada (si existia).\n";
                } catch (const std::exception& e) {
                    std::cout << "[X] Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                std::string src, dest;
                std::cout << "Vertice Origen: ";
                std::cin >> src;
                std::cout << "Vertice Destino: ";
                std::cin >> dest;
                bool existe = graph->hasEdge(src, dest);
                std::cout << "Resultado: " << (existe ? "SI existe arista." : "NO existe arista.") << "\n";
                break;
            }
            case 5: {
                graph->printGraph();
                break;
            }
            case 6: {
                std::string start;
                std::cout << "Vertice de inicio para BFS: ";
                std::cin >> start;
                try {
                    SimpleGraph::CustomVector<std::string> bfsRes = graph->BFS(start);
                    std::cout << "\n--> Recorrido BFS: ";
                    for (int i = 0; i < bfsRes.size(); i++) {
                        std::cout << bfsRes.at(i) << " ";
                    }
                    std::cout << "\n";
                } catch (const std::exception& e) {
                    std::cout << "[X] Error: " << e.what() << "\n";
                }
                break;
            }
            case 7: {
                std::string start;
                std::cout << "Vertice de inicio para DFS: ";
                std::cin >> start;
                try {
                    SimpleGraph::CustomVector<std::string> dfsRes = graph->DFS(start);
                    std::cout << "\n--> Recorrido DFS: ";
                    for (int i = 0; i < dfsRes.size(); i++) {
                        std::cout << dfsRes.at(i) << " ";
                    }
                    std::cout << "\n";
                } catch (const std::exception& e) {
                    std::cout << "[X] Error: " << e.what() << "\n";
                }
                break;
            }
            case 8: {
                std::string start, end;
                std::cout << "Vertice Origen: ";
                std::cin >> start;
                std::cout << "Vertice Destino: ";
                std::cin >> end;
                try {
                    SimpleGraph::PathResult<std::string> res = graph->shortestPathDijkstra(start, end);
                    if (res.path.size() == 0) {
                        std::cout << "\n[!] No existe conexion/camino entre '" << start << "' y '" << end << "'.\n";
                    } else {
                        std::cout << "\n--> RUTA OPTIMA (Dijkstra):\n    Camino: ";
                        for (int i = 0; i < res.path.size(); i++) {
                            std::cout << res.path.at(i) << (i + 1 < res.path.size() ? " -> " : "");
                        }
                        std::cout << "\n    Distancia Total: " << res.totalDistance << "\n";
                    }
                } catch (const std::exception& e) {
                    std::cout << "[X] Error: " << e.what() << "\n";
                }
                break;
            }
            case 9: {
                cargarGrafoDePrueba(graph);
                break;
            }
            case 10:
                std::cout << "Regresando al menu principal...\n";
                break;
            default:
                std::cout << "[!] Opcion no valida.\n";
        }
    } while (option != 10);
}

int main() {
    int mainOption = 0;

    do {
        std::cout << "\n==========================================\n";
        std::cout << "   SISTEMA DE GESTION DE GRAFOS (NO-STL)  \n";
        std::cout << "==========================================\n";
        std::cout << "1. Lista de Adyacencia (GraphList)\n";
        std::cout << "2. Matriz de Adyacencia (GraphMatrix)\n";
        std::cout << "3. Salir del Programa\n";
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> mainOption)) {
            std::cout << "\n[!] Entrada invalida. Ingrese un numero.\n";
            clearBuffer();
            continue;
        }

        if (mainOption == 1 || mainOption == 2) {
            std::cout << "\nTipo de Grafo:\n1. No Dirigido\n2. Dirigido\nOpcion: ";
            int type;
            std::cin >> type;
            bool isDirected = (type == 2);

            SimpleGraph::AbstractGraph<std::string>* graph = nullptr;

            if (mainOption == 1) {
                graph = new SimpleGraph::GraphList<std::string>(isDirected);
                menuPolimorfico(graph, "LISTA DE ADYACENCIA");
            } else {
                graph = new SimpleGraph::GraphMatrix<std::string>(isDirected);
                menuPolimorfico(graph, "MATRIZ DE ADYACENCIA");
            }

            delete graph;
        } else if (mainOption == 3) {
            std::cout << "\n¡Saliendo del programa!\n";
        } else {
            std::cout << "[!] Opcion no valida.\n";
        }
    } while (mainOption != 3);

    return 0;
}