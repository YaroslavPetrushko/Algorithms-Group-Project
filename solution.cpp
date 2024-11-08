// Back-end complete function Template for C++
#include "solution.h"
#include <algorithm>
#include <iostream>
#include <limits.h> // Для INT_MAX
#include <stack>
#include <unordered_map> // Для std::unordered_map
using namespace std;

pair<int, vector<int>> Solution::ChinesePostmanProblem(const vector<vector<int>>& e, int n) {
    if (n == 0)
        return { -1, {} };

    vector<int> oddVertices; // Stores nodes with odd degree.
    vector<vector<pair<int, int>>> graph(n); // Adjacency list representation of the graph.
    int totalWeight = 0; // Sum of all edge weights in the graph.

    // Create adjacency list and calculate the total weight.
    for (auto& edge : e) {
        totalWeight += edge[2];
        graph[edge[0] - 1].push_back({ edge[1] - 1, edge[2] });
        graph[edge[1] - 1].push_back({ edge[0] - 1, edge[2] });
    }

    // Find vertices with odd degrees.
    for (int i = 0; i < n; i++) {
        if (graph[i].size() % 2) {
            oddVertices.push_back(i);
        }
    }

    if (oddVertices.empty())
        return { totalWeight, {} }; // Already Eulerian.

    // Calculate shortest paths between all odd degree vertices using Floyd-Warshall or Dijkstra.
    vector<vector<int>> shortestPath = floydWarshalls(graph, n);
    vector<pair<int, int>> additionalEdges; // Edges to be added to make the graph Eulerian.

    // Generate pairs of odd vertices to find the minimum weight matching.
    vector<vector<pair<int, int>>> oddPairs;
    vector<pair<int, int>> currentPair;
    vector<bool> visited(oddVertices.size(), false);
    generatePairs(oddVertices, 0, oddPairs, currentPair, visited);

    int minDistance = INT_MAX;
    for (auto& pairs : oddPairs) {
        int tempDist = 0;
        vector<pair<int, int>> tempEdges;
        for (auto& p : pairs) {
            if (shortestPath[p.first][p.second] == INT_MAX) {
                tempDist = INT_MAX;
                break;
            }
            tempDist += shortestPath[p.first][p.second];
            tempEdges.push_back({ p.first, p.second });
        }
        if (tempDist < minDistance) {
            minDistance = tempDist;
            additionalEdges = tempEdges;
        }
    }

    if (minDistance == INT_MAX)
        return { -1, {} }; // No possible Eulerian cycle.

    // Add edges from the additional matching.
    for (auto& edge : additionalEdges) {
        int u = oddVertices[edge.first];
        int v = oddVertices[edge.second];
        graph[u].push_back({ v, shortestPath[edge.first][edge.second] });
        graph[v].push_back({ u, shortestPath[edge.second][edge.first] });
    }

    // Now, we need to find an Eulerian cycle in the modified graph.
    list<int> eulerianCycle = findEulerianCycle(graph, n); // This should be defined to find the cycle

    vector<int> vertexSequence(eulerianCycle.begin(), eulerianCycle.end()); // Convert list to vector

    return { totalWeight + minDistance, vertexSequence };
}

    void Solution::generatePairs(const vector<int>& oddVertices, int index, vector<vector<pair<int, int>>>& allPairs, vector<pair<int, int>>& current, vector<bool>& visited)
    {
        // Base case: If we've paired up all odd vertices
        if (current.size() == oddVertices.size() / 2) {
            allPairs.push_back(current);
            return;
        }

        // Try pairing the current vertex with every unvisited vertex
        for (int i = index; i < oddVertices.size(); ++i) {
            if (!visited[i]) {
                visited[i] = true; // Mark current vertex as visited
                for (int j = i + 1; j < oddVertices.size(); ++j) {
                    if (!visited[j]) {
                        visited[j] = true; // Mark paired vertex as visited
                        current.push_back({ i, j }); // Add the pair

                        generatePairs(oddVertices, i, allPairs, current, visited); // Recur

                        // Backtrack
                        visited[j] = false;
                        current.pop_back();
                    }
                }
                visited[i] = false; // Unmark current vertex
                break; // Move to the next vertex
            }
        }
    }

    // Функція для пошуку найкоротших відстаней між усіма парами вузлів з використанням алгоритму Флойда-Уоршалла.
    vector<vector<int>> Solution::floydWarshalls(const vector<vector<pair<int, int>>>& graph, int n)
    {
        // Ініціалізація матриці відстаней з безкінечністю.
        vector<vector<int>> d(n, vector<int>(n, INT_MAX));

        // Встановлюємо діагональні елементи в 0.
        for (int i = 0; i < n; i++)
            d[i][i] = 0;

        // Оновлюємо матрицю відстаней з прямими ребрами, що є в графі.
        for (int i = 0; i < n; i++)
        {
            for (auto j : graph[i])
                d[i][j.first] = j.second;
        }

        // Обчислюємо найкороткі відстані за допомогою алгоритму Флойда-Уоршалла.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (d[i][k] != INT_MAX && d[k][j] != INT_MAX)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }

        // Повертаємо матрицю найкоротких відстаней.
        return d;
    }

    list<int> Solution::findEulerianCycle(vector<vector<pair<int, int>>>& graph, int n) {
        list<int> cycle;
        stack<int> currentPath;
        vector<int> edgeCount(n, 0);

        // Count edges for each vertex
        for (int i = 0; i < n; i++) {
            edgeCount[i] = graph[i].size();
        }

        currentPath.push(0); // Start from vertex 0.

        while (!currentPath.empty()) {
            int u = currentPath.top();
            if (edgeCount[u] == 0) {
                cycle.push_front(u); // Add to cycle when all edges are visited.
                currentPath.pop();
            }
            else {
                for (auto& neighbor : graph[u]) {
                    if (edgeCount[u] > 0) {
                        // Remove the edge from the graph
                        edgeCount[u]--;
                        edgeCount[neighbor.first]--;

                        // Add the neighbor to the current path
                        currentPath.push(neighbor.first);
                        break; // Move to the next vertex
                    }
                }
            }
        }

        return cycle;
    }


