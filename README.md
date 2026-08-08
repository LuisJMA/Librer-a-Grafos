# Librer-a-Grafos
# Librer-a-Grafos
Características Principales

* **Cero Dependencias de STL Internas:** Implementación propia de estructuras dinámicas (`CustomVector` y `CustomQueue`).
* **Soporte Genérico (`template <typename T>`):** Permite trabajar con cualquier tipo de dato primario (`int`, `char`, `double`) o complejo (`std::string`, estructuras personalizadas).
* **Diseño Polimórfico Orientado a Objetos:** Clase base abstracta `AbstractGraph<T>` que unifica la interfaz entre ambas representaciones del grafo.
* **Resistencia a Fallos y Manejo Seguro de Memoria:**
  * Acceso a memoria controlado con validación de fronteras (`at()`) mediante excepciones (`std::out_of_range`).
  * Reasignación dinámica de capacidad para evitar desbordamientos (*overflow*).
  * Cumplimiento estricto de la **Regla de los Tres** (*Rule of 3*) en contenedores para prevenir *memory leaks*.
  * Destructores virtuales para la correcta liberación de memoria dinámica bajo polimorfismo.
* **Algoritmos Fundamentales Incluidos:**
  * **BFS** (*Breadth-First Search* / Búsqueda en Anchura).
  * **DFS** (*Depth-First Search* / Búsqueda en Profundidad).
  * **Dijkstra** (Camino más corto con pesos y reconstrucción exacta de la ruta mediante `PathResult<T>`).

---

## 📁 Estructura del Proyecto

El proyecto sigue una organización modular limpia separando declaraciones (`include/`) de implementaciones (`src/`):

```text
.
├── include/
│   ├── AbstractGraph.hpp   # Interfaz abstracta base (Polimorfismo)
│   ├── CustomQueue.hpp     # Cola dinamica propia (Rule of 3)
│   ├── CustomVector.hpp    # Vector dinámico propio (Safe index checking)
│   ├── GraphList.hpp       # Implementacion por Lista de Adyacencia
│   └── GraphMatrix.hpp     # Implementacion por Matriz de Adyacencia
├── src/
│   ├── CustomQueue.cpp
│   ├── CustomVector.cpp
│   ├── GraphList.cpp
│   └── GraphMatrix.cpp
├── main.cpp                # Menu interactivo de pruebas y demostracion
└── README.md
Métodos de la Interfaz (AbstractGraph<T>)
Cualquier instancia de GraphList<T> o GraphMatrix<T> dispone de las siguientes funciones clave:
Cualquier instancia de `GraphList<T>` o `GraphMatrix<T>` dispone de las siguientes funciones clave:

| Método |                               | Descripción |
| :--- | :--- |
| `addVertex(const T& vertex)` | Agrega un nuevo nodo/vértice al grafo si no existe. |
| `addEdge(src, dest, weight)` | Conecta dos vértices con un peso determinado. |
| `removeEdge(src, dest)` | Elimina la conexión especificada entre dos vértices. |
| `hasEdge(src, dest)` | Retorna `true` si existe una arista directa entre ambos nodos. |
| `printGraph()` | Imprime la estructura gráfica por consola (lista o matriz). |
| `BFS(startVertex)` | Ejecuta recorrido en anchura retornando un `CustomVector<T>`. |
| `DFS(startVertex)` | Ejecuta recorrido en profundidad retornando un `CustomVector<T>`. |
| `shortestPathDijkstra(start, end)` | Calcula la ruta óptima retornando un `PathResult<T>` (ruta y costo total). |

Compilacion y ejecucion.
g++ -std=c++11 main.cpp -o libreria_grafos
