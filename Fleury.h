// A C++ program print Eulerian Trail in a given Eulerian or
// Semi-Eulerian Graph
#include <algorithm>
#include <iostream>
#include <list>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

// A class that represents an undirected graph
class Graph {
    int V; // No. of vertices
    list<int>* adj; // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    // functions to add and remove edge
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void rmvEdge(int u, int v);

    // Methods to print Eulerian tour
    void printEulerTour(const vector<pair<int, int>>& additionalEdges);
    void printEulerUtil(int s);

    //Отримання загальної ваги ребер
    int getTotalWeight(const vector<vector<int>>& edges);

    // This function returns count of vertices reachable
    // from v. It does DFS
    int DFSCount(int v, bool visited[]);

    // Utility function to check if edge u-v is a valid next
    // edge in Eulerian trail or circuit
    bool isValidNextEdge(int u, int v);

private:
    vector<pair<int, int>> e; // Вектор для зберігання ребер графа
};
