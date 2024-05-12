#include <vector>
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected") {
    ariel::Graph g;

    // Test Case 1: Simple connected graph
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    // Test Case 2: Simple disconnected graph
    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // Test Case 3: Large connected graph
    vector<vector<int>> graph3 = {
            {0, 1, 1, 0},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {0, 1, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    // Test Case 4: Large disconnected graph
    vector<vector<int>> graph4 = {
            {0, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == false);


    // Test Case 6: Single vertex graph
    vector<vector<int>> graph6 = {
            {0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    // Test Case 7: Two vertices connected
    vector<vector<int>> graph7 = {
            {0, 1},
            {1, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    // Test Case 8: Two vertices disconnected
    vector<vector<int>> graph8 = {
            {0, 0},
            {0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // Test Case 9: Three vertices, two connected, one isolated
    vector<vector<int>> graph9 = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // Test Case 10: Three vertices in a line
    vector<vector<int>> graph10 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph10);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test shortestPath") {
    ariel::Graph g;

    // Test Case 1: Simple path
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    // Test Case 2: No path available
    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    // Test Case 3: Direct path
    vector<vector<int>> graph3 = {
            {0, 1},
            {1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");

    // Test Case 4: Path with multiple steps
    vector<vector<int>> graph4 = {
            {0, 1, 0, 0, 0},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {0, 0, 0, 1, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->2->3->4");


    // Test Case 6: Single vertex graph
    vector<vector<int>> graph6 = {
            {0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "0");

    // Test Case 7: Path in a cycle
    vector<vector<int>> graph7 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");

    // Test Case 8: Multiple shortest paths
    vector<vector<int>> graph8 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");

    // Test Case 9: Disconnected graph
    vector<vector<int>> graph9 = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "-1");

    // Test Case 10: Path through a hub
    vector<vector<int>> graph10 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
    g.loadGraph(graph10);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
}

TEST_CASE("Test isContainsCycle") {
    ariel::Graph g;

    // Test Case 1: No cycle
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    // Test Case 2: Contains cycle
    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    // Test Case 3: Large graph with cycle
    vector<vector<int>> graph3 = {
            {0, 1, 1, 0},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {0, 1, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    // Test Case 4: Large graph without cycle
    vector<vector<int>> graph4 = {
            {0, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);


    // Test Case 6: Single vertex graph
    vector<vector<int>> graph6 = {
            {0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    // Test Case 7: Two vertices connected
    vector<vector<int>> graph7 = {
            {0, 1},
            {1, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    // Test Case 8: Two vertices disconnected
    vector<vector<int>> graph8 = {
            {0, 0},
            {0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    // Test Case 9: Three vertices in a line
    vector<vector<int>> graph9 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    // Test Case 10: Three vertices in a cycle
    vector<vector<int>> graph10 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
    g.loadGraph(graph10);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("Test isBipartite") {
    ariel::Graph g;

    // Test Case 1: Simple bipartite graph
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    // Test Case 2: Non-bipartite graph
    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");


    vector<vector<int>> graph4 = {{0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={}");  // Single vertex is bipartite

    // Test Case 6: Two vertices connected
    vector<vector<int>> graph6 = {
            {0, 1},
            {1, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}");

    // Test Case 7: Two vertices disconnected
    vector<vector<int>> graph7 = {
            {0, 0},
            {0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1}, B={}");

    // Test Case 8: Three vertices in a line
    vector<vector<int>> graph8 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    // Test Case 9: Three vertices in a triangle (non-bipartite)
    vector<vector<int>> graph9 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    // Test Case 10: Four vertices in a square (bipartite)
    vector<vector<int>> graph10 = {
            {0, 1, 0, 1},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {1, 0, 1, 0}};
    g.loadGraph(graph10);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}


TEST_CASE("Test negativeCycle") {
    ariel::Graph g;

    // Test Case 1: Graph with no negative cycle
    vector<vector<int>> graph1 = {
            {0, 1, 4, 0, 0},
            {1, 0, 4, 2, 7},
            {4, 4, 0, 3, 0},
            {0, 2, 3, 0, 1},
            {0, 7, 0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative weight cycle found.");

    // Test Case 2: Graph with a negative cycle
    vector<vector<int>> graph2 = {
            {0, -1, 4},
            {-1, 0, -2},
            {4, -2, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative weight cycle.");

    // Test Case 3: Larger graph with negative cycle
    vector<vector<int>> graph3 = {
            {0, 1, 4, 0, 0},
            {1, 0, -4, 2, 7},
            {4, -4, 0, 3, 0},
            {0, 2, 3, 0, 1},
            {0, 7, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative weight cycle.");

    // Test Case 4: Disconnected graph with negative cycle
    vector<vector<int>> graph4 = {
            {0, 1, 0, 0},
            {1, 0, -1, 0},
            {0, -1, 0, 1},
            {0, 0, 1, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative weight cycle.");

    // Test Case 6: Single vertex graph
    vector<vector<int>> graph6 = {
            {0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative weight cycle found.");

    // Test Case 7: Two vertices connected, no negative cycle
    vector<vector<int>> graph7 = {
            {0, 1},
            {1, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative weight cycle found.");

    // Test Case 8: Two vertices connected with negative cycle
    vector<vector<int>> graph8 = {
            {0, -1},
            {-1, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative weight cycle.");

    // Test Case 9: Three vertices with a negative cycle
    vector<vector<int>> graph9 = {
            {0, 1, 0},
            {1, 0, -1},
            {0, -1, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative weight cycle.");

    // Test Case 10: Complex graph with mixed weights
    vector<vector<int>> graph10 = {
            {0, 3, 0, 0, 0, -1},
            {3, 0, 2, 0, 0, 0},
            {0, 2, 0, 5, 0, 0},
            {0, 0, 5, 0, 1, 0},
            {0, 0, 0, 1, 0, 4},
            {-1, 0, 0, 0, 4, 0}};
    g.loadGraph(graph10);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative weight cycle.");
    cout<<"all the tests passed"<<endl;
}

