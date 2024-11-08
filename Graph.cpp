
#include "Graph.h"
using namespace std;

vector<pair<int, int>> Graph::getEulerPath(const vector<pair<int, int>>& additionalEdges) {
    // Додаємо додаткові ребра в граф
    for (const auto& edge : additionalEdges) {
        addEdge(edge.first, edge.second);
    }

    // Знаходимо вершину з непарною степенем, якщо така є
    int u = 0;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() & 1) {
            u = i;
            break;
        }
    }

    vector<pair<int, int>> eulerPath;
    getEulerPathUtil(u, eulerPath);  // Викликаємо допоміжну функцію для отримання шляху
    
    return eulerPath;
}

void Graph::getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath) {
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (v != -1 && isValidNextEdge(u, v)) {
            eulerPath.push_back({ u, v });  // Додаємо пару (u, v) до шляху
            rmvEdge(u, v);
            getEulerPathUtil(v, eulerPath);  // Рекурсивно викликаємо для наступної вершини
        }
    }
}

void Graph::printEulerTour(const vector<pair<int, int>>& previousPath) {
    cout << "Ейлеровий маршрут :\n";
    for (const auto& edge : previousPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";  // Виводимо шлях, щоб перевірити, чи він зберігся
    }
    cout << endl;
}

//void Graph::printEulerUtil(int u) {
//    list<int>::iterator i;
//    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
//        int v = *i;
//        if (v != -1 && isValidNextEdge(u, v)) {
//            cout << (u + 1) << "-" << (v + 1) << " ";
//            rmvEdge(u, v);
//            printEulerUtil(v);
//        }
//    }
//}

void Graph::printEulerExtend(const vector<pair<int, int>>& previousPath,
    const vector<pair<int, int>>& additionalEdges,
    const vector<pair<int, int>>& newPath) {
    cout << "=== Дебаг інформація ===\n";

    // Виведення попереднього шляху
    cout << "Попередній шлях:\n";
    for (const auto& edge : previousPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;

    // Виведення додаткових ребер
    cout << "Додаткові ребра для доповнення:\n";
    for (const auto& edge : additionalEdges) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;

    // Виведення оновленого шляху
    cout << "Оновлений Ейлеровий шлях:\n";
    for (const auto& edge : newPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << "\n=======================\n";
}


// Функція для перевірки наявності ребра в графі
bool Graph::edgeExists(int u, int v) {
    for (auto& neighbor : adj[u]) {
        if (neighbor == v) return true;
    }
    return false;
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