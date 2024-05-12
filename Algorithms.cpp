#include "Algorithms.hpp"
#include "Graph.hpp"
#include <limits>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace ariel;
using namespace std;

bool isCycleHelper(int v, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& parent, int& cycle_start, int& cycle_end);

// Check if the graph is connected using BFS
bool Algorithms::isConnected(const Graph& g) {
    size_t numV = static_cast<size_t>(g.getNumVertices());
    if (numV == 0) return true; // An empty graph is trivially connected

    vector<bool> visited(numV, false);
    queue<size_t> q;
    visited[0] = true; // Start BFS from vertex 0
    q.push(0);

    while (!q.empty()) {
        size_t curr = q.front();
        q.pop();

        // Check the neighbors of curr
        for (size_t i = 0; i < numV; ++i) {
            if (g.getMatrix()[curr][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    // The graph is connected if all vertices were visited
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

// Find the shortest path using BFS
string Algorithms::shortestPath(const Graph& g, size_t start, size_t end) {
    size_t numV = static_cast<size_t>(g.getNumVertices());
    if (start == end) return to_string(start);  // If start and end are the same

    vector<bool> visited(numV, false);
    vector<int> distance(numV, -1);  // Distance from start to each vertex
    vector<int> predecessor(numV, -1);  // To build the path
    queue<size_t> queue;

    // Start from the initial vertex
    visited[start] = true;
    distance[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        size_t current = queue.front();
        queue.pop();

        // Explore the neighbors
        for (size_t i = 0; i < numV; ++i) {
            if (g.getMatrix()[current][i] > 0 && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[current] + 1;
                predecessor[i] = static_cast<int>(current);
                queue.push(i);

                if (i == end) {
                    // After reaching the end vertex, build the path
                    vector<int> path;
                    for (int crawl = static_cast<int>(end); crawl != -1; crawl = predecessor[crawl]) {
                        path.push_back(crawl);
                    }

                    // Reverse the path
                    reverse(path.begin(), path.end());

                    // Convert the path to a string
                    stringstream pathStream;
                    for (size_t j = 0; j < path.size(); ++j) {
                        if (j > 0) pathStream << "->";
                        pathStream << path[j];
                    }
                    return pathStream.str();
                }
            }
        }
    }

    // If no path found
    return "-1";
}

// Detect if the graph contains a cycle using DFS
bool Algorithms::isContainsCycle(const Graph& g) {
    size_t numV = static_cast<size_t>(g.getNumVertices());
    vector<bool> visited(numV, false);
    vector<int> parent(numV, -1);
    int cycle_start = -1, cycle_end = -1;
    const vector<vector<int>>& adj = g.getAdjList();

    for (size_t i = 0; i < numV; ++i) {
        if (!visited[i] && isCycleHelper(static_cast<int>(i), adj, visited, parent, cycle_start, cycle_end)) {
            if (cycle_start != -1) {
                vector<int> cycle;
                cycle.push_back(cycle_start);
                for (int v = cycle_end; v != cycle_start; v = parent[v]) {
                    cycle.push_back(v);
                }
                cycle.push_back(cycle_start);
                reverse(cycle.begin(), cycle.end());

                cout << "The cycle is: ";
                for (size_t j = 0; j < cycle.size(); ++j) {
                    if (j > 0) cout << "->";
                    cout << cycle[j];
                }
                cout << endl;
            }
            return true;
        }
    }
    return false;
}

// Check if the graph is bipartite using BFS
string Algorithms::isBipartite(const Graph& g) {
    size_t numV = static_cast<size_t>(g.getNumVertices());
    if (numV == 0) return "The graph is bipartite: A={}, B={}"; // An empty graph is trivially bipartite

    vector<int> color(numV, -1);  // -1 indicates uncolored
    queue<size_t> q;

    // This loop ensures that we cover disconnected components as well
    for (size_t start = 0; start < numV; ++start) {
        if (color[start] == -1) {  // If this vertex has not been colored, it means it's a new component
            color[start] = 0;
            q.push(start);

            while (!q.empty()) {
                size_t u = q.front();
                q.pop();

                for (size_t v = 0; v < g.getAdjList()[u].size(); ++v) {
                    int neighbor = g.getAdjList()[u][v];
                    if (color[neighbor] == -1) {  // If vertex is uncolored, color it with alternate color
                        color[neighbor] = 1 - color[u];
                        q.push(neighbor);
                    } else if (color[neighbor] == color[u]) {  // If the neighbor has the same color, graph is not bipartite
                        return "0";  // Return false or 0 indicating not bipartite
                    }
                }
            }
        }
    }

    // Collect and return bipartite sets A and B
    stringstream ss;
    ss << "The graph is bipartite: A={";
    bool first = true;
    for (size_t i = 0; i < numV; ++i) {
        if (color[i] == 0) {
            if (!first) ss << ", ";
            ss << i;
            first = false;
        }
    }
    ss << "}, B={";
    first = true;
    for (size_t i = 0; i < numV; ++i) {
        if (color[i] == 1) {
            if (!first) ss << ", ";
            ss << i;
            first = false;
        }
    }
    ss << "}";
    return ss.str();
}

// Detect negative cycle using Bellman-Ford algorithm
string Algorithms::negativeCycle(const Graph& g) {
    size_t numV = static_cast<size_t>(g.getNumVertices());
    const vector<vector<int>>& matrix = g.getMatrix();

    // Initialize distances to infinity, except for a starting point (arbitrarily chosen as vertex 0)
    vector<int> dist(numV, numeric_limits<int>::max());
    if (numV > 0)
        dist[0] = 0;

    // Relax edges up to V-1 times
    for (size_t i = 0; i < numV - 1; i++) {
        for (size_t u = 0; u < numV; u++) {
            for (size_t v = 0; v < numV; v++) {
                if (matrix[u][v] != 0) { // There is an edge from u to v
                    int weight = matrix[u][v];
                    if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
    }

    // Check for negative weight cycle
    for (size_t u = 0; u < numV; u++) {
        for (size_t v = 0; v < numV; v++) {
            if (matrix[u][v] != 0) { // There is an edge from u to v
                int weight = matrix[u][v];
                if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    return "The graph contains a negative weight cycle.";
                }
            }
        }
    }

    return "No negative weight cycle found.";
}

bool isCycleHelper(int v, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& parent, int& cycle_start, int& cycle_end) {
    visited[v] = true;

    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            parent[neighbor] = v;
            if (isCycleHelper(neighbor, adj, visited, parent, cycle_start, cycle_end))
                return true;
        } else if (neighbor != parent[v]) {
            // If an adjacent vertex is visited and not the parent of the current vertex, then there is a cycle
            cycle_start = neighbor;
            cycle_end = v;
            return true;
        }
    }
    return false;
}

