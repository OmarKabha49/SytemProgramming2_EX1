// Graph.hpp
// Author: Omar Kabha

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel {

    class Graph {

    private:
        vector<vector<int>> Matrix; // Adjacency matrix
        vector<vector<int>> adjList; // Adjacency list
        int numVertices; // Number of vertices
        int numEdges; // Number of edges

    public:
        // Constructor
        Graph();

        // Load a graph from an adjacency matrix
        void loadGraph(const vector<vector<int>>& matrix);

        // Print the graph
        void printGraph() const;

        // Get the adjacency list
        const vector<vector<int>>& getAdjList() const;

        // Get the adjacency matrix
        const vector<vector<int>> &getMatrix() const;

        // Get the number of vertices
        int getNumVertices() const;
    };

}  // namespace ariel

#endif