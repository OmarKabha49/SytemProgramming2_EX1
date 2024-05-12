# SytemProgramming2_EX1
# Graph Algorithms in C++

This project implements a simple graph library in C++ with basic algorithms for connectivity and pathfinding. The main components of the project are the `Graph` class and the `Algorithms` class.

## Files

- `Graph.hpp`:
  - Header file for the `Graph` class.
  - Declares the members and methods for managing graphs.
- `Graph.cpp`:
  - Implementation file for the `Graph` class.
  - Defines the methods for loading, printing, and accessing graph data.
- `Algorithms.hpp`:
  - Header file for the `Algorithms` class.
  - Declares algorithms for checking connectivity and finding paths.
- `Algorithms.cpp`:
  - Implementation file for the `Algorithms` class.
  - Defines algorithms for checking if a graph is connected and finding the shortest path between vertices.

## Classes

### Graph

Represents a graph using an adjacency matrix and an adjacency list.

- **Methods:**
  - `Graph()`: Constructor to initialize an empty graph.
  - `void loadGraph(const vector<vector<int>>& matrix)`: Loads a graph from an adjacency matrix.
  - `void printGraph() const`: Prints a summary of the graph.
  - `const vector<vector<int>>& getMatrix() const`: Returns the adjacency matrix.
  - `const vector<vector<int>>& getAdjList() const`: Returns the adjacency list.
  - `int getNumVertices() const`: Returns the number of vertices in the graph.

## Algorithms Class
The `Algorithms` class provides the following static methods for graph algorithms:
- `static bool isConnected(const Graph& g)`: Checks if the graph is connected.
- `static std::string shortestPath(const Graph& g, int start, int end)`: Finds the shortest path between two vertices in the graph.
- `static bool isContainsCycle(const Graph& g)`: Checks if the graph contains a cycle and prints it if it does.
- `static std::string isBipartite(const Graph& g)`: Checks if the graph is bipartite and returns the partition.
- `static bool negativeCycle(const Graph& g)`: Checks if the graph contains a negative weight cycle.
