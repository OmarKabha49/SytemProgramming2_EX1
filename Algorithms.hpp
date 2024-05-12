// Algorithms.hpp
// Author: Omar Kabha

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel {

    class Algorithms {
    public:
        // Determines if the graph is fully connected using BFS.
        static bool isConnected(const Graph& g);

        // Finds the shortest path between two vertices using BFS for unweighted graphs.
        static std::string shortestPath(const Graph& g, size_t start, size_t end);

        // Checks if there is any cycle in the graph using DFS.
        static bool isContainsCycle(const Graph& g);

        // Determines if the graph can be colored with two colors such that no two adjacent vertices share the same color using BFS.
        static std::string isBipartite(const Graph& g);

        // Detects the presence of a negative weight cycle accessible from any vertex using the Bellman-Ford algorithm.
        static std::string negativeCycle(const Graph& g);
    };
}

#endif // ALGORITHMS_HPP
