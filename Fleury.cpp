
#include "Fleury.h"
using namespace std;

void Graph::printEulerTour()
{
    // Find a vertex with odd degree
    int u = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1) {
            u = i;
            break;
        }

    // Print tour starting from oddv
    printEulerUtil(u);
    cout << endl;
}

// Print Euler tour starting from vertex u
void Graph::printEulerUtil(int u)
{
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;

        // If edge u-v is not removed and it's a valid
        // next edge
        if (v != -1 && isValidNextEdge(u, v)) {
            cout << (u + 1) << "-" << (v + 1) << " "; // Output in 1-based format
            rmvEdge(u, v);
            printEulerUtil(v);
        }
    }
}

// Метод для обрахування загальної ваги ребер
int Graph::getTotalWeight(const vector<vector<int>>& edges) {
    int totalWeight = 0;
    for (const auto& edge : edges) {
        totalWeight += edge[2]; // The weight is the third element
    }
    return totalWeight;
}

// The function to check if edge u-v can be considered as next edge in Euler Tour
bool Graph::isValidNextEdge(int u, int v)
{
    // The edge u-v is valid in one of the following two
    // cases:

    // 1) If v is the only adjacent vertex of u
    int count = 0; // To store count of adjacent vertices
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1)
            count++;
    if (count == 1)
        return true;

    // 2) If there are multiple adjacents, then u-v is not a
    // bridge Do following steps to check if u-v is a bridge

    // 2.a) count of vertices reachable from u
    bool* visited = new bool[V];
    memset(visited, false, V * sizeof(bool));
    int count1 = DFSCount(u, visited);

    // 2.b) Remove edge (u, v) and after removing the edge,
    // count vertices reachable from u
    rmvEdge(u, v);
    memset(visited, false, V * sizeof(bool));
    int count2 = DFSCount(u, visited);

    // 2.c) Add the edge back to the graph
    addEdge(u, v);

    delete[] visited;

    // 2.d) If count1 is greater, then edge (u, v) is a bridge
    return (count1 > count2) ? false : true;
}

// This function removes edge u-v from graph. It removes the edge by replacing adjacent vertex value with -1.
void Graph::rmvEdge(int u, int v)
{
    // Find v in adjacency list of u and replace it with -1
    list<int>::iterator iv
        = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;

    // Find u in adjacency list of v and replace it with -1
    list<int>::iterator iu
        = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}

// A DFS based function to count reachable vertices from v
int Graph::DFSCount(int v, bool visited[])
{
    // Mark the current node as visited
    visited[v] = true;
    int count = 1;

    // Recur for all vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i])
            count += DFSCount(*i, visited);

    return count;
}