// Graph.cpp
// Author: Omar Kabha

#include "Graph.hpp"

using namespace ariel;
using namespace std;

#include "Graph.hpp"

using namespace ariel;
using namespace std;

// Constructor
Graph::Graph() : numVertices(0), numEdges(0) {}

// Load a graph from an adjacency matrix
void Graph::loadGraph(const vector<vector<int>>& matrix) {
    if (matrix.size() == 0 || matrix.size() != matrix[0].size()) {
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
    numVertices = matrix.size();
    numEdges = 0;
    Matrix = matrix;
    adjList.resize(numVertices);  // Changed from reserve to resize for direct indexing

    for (size_t i = 0; i < numVertices; ++i) {
        adjList[i].clear();
        for (size_t j = 0; j < numVertices; ++j) {
            if (Matrix[i][j] > 0) {
                numEdges += 1;
                adjList[i].push_back(j);
            }
        }
    }
}

// Print the graph
void Graph::printGraph() const {
    cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges.\n";
}

// Get the adjacency matrix
const vector<vector<int>>& Graph::getMatrix() const {
    return Matrix;
}

// Get the number of vertices
int Graph::getNumVertices() const {
    return numVertices;
}

// Get the adjacency list
const vector<vector<int>>& Graph::getAdjList() const {
    return adjList;
}