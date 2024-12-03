//Функціонал для вирішення проблеми китайського листоноші, 
// здебільшого для знаходження мінімальної довжини та додаткових ребер
#include "Solution.h"
using namespace std;

// Алгоритм Дейкстри для визначення найкоротших шляхів від однієї вершини до всіх інших
vector<int> Solution::dijkstra(int src, const vector<vector<pair<int, int>>>& g, int n) {

    vector<int> dist(n, INT_MAX); // Відстані від джерела до всіх вершин
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    pq.push({ 0, src });
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[u]) continue;

        for (auto& neighbor : g[u]) {
            int v = neighbor.first, weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

// Рекурсивна функція для генерації всіх можливих пар непарних вузлів
void Solution::generateOddPairs(const vector<int>& oddNodes, int index,
    vector<vector<pair<int, int>>>& allOddPairs,
    vector<pair<int, int>>& currentPair,
    vector<bool>& visited) {

    if (index == oddNodes.size()) {
        allOddPairs.push_back(currentPair);
        return;
    }

    if (visited[index]) {
        generateOddPairs(oddNodes, index + 1, allOddPairs, currentPair, visited);
        return;
    }

    visited[index] = true;
    for (int j = 0; j < oddNodes.size(); ++j) {

        if (!visited[j]) {
            visited[j] = true;
            currentPair.push_back({ oddNodes[index], oddNodes[j] });
            generateOddPairs(oddNodes, index + 1, allOddPairs, currentPair, visited);
            currentPair.pop_back(); // Повертаємо стан
            visited[j] = false;
        }

    }

    visited[index] = false;
}

// Пошук найкоротшого шляху між двома вершинами через проміжні вершини
pair<int, vector<pair<int, int>>> Solution::findVertexPath(int u, int v,
    const vector<vector<pair<int, int>>>& g, vector<pair<int, int>>& tempEdges,
    const vector<vector<int>>& shortestPath, int n) {

    vector<pair<int, int>> bestPath;
    int minPath = INT_MAX;


    for (int k = 0; k < n; ++k) {

        if (k != u && k != v && shortestPath[u][k] < INT_MAX && shortestPath[k][v] < INT_MAX) {

            int pathLength = shortestPath[u][k] + shortestPath[k][v];

            if (pathLength < minPath) {
                minPath = pathLength;
                bestPath = { {u, k}, {k, v} };
            }
        }
    }

    if (minPath < INT_MAX) {
        tempEdges.insert(tempEdges.end(), bestPath.begin(), bestPath.end());
    }

    return { minPath, bestPath };
}

// Основна функція для розв'язання китайської задачі листоноші
vector<pair<int, int>> Solution::chinesePostmanProblem(vector<vector<int>>& edges, int n) {
   
    if (n == 0) return { }; // Повертаємо null, якщо граф порожній.

    vector<int> oddNodes; // Масив для збереження вузлів з непарним степенем
    vector<vector<pair<int, int>>> g(n); // Список ребер графу

    // Створення графу та пошук непарних вузлів
    for (const auto& edge : edges) {
        g[edge[0] - 1].push_back({ edge[1] - 1, edge[2] });
        g[edge[1] - 1].push_back({ edge[0] - 1, edge[2] });
    }

    // Знаходимо вузли з непарним степенем
    for (int i = 0; i < n; i++) {

        if (g[i].size() % 2)
            oddNodes.push_back(i);
    }

    if (oddNodes.size() == 0)
        return { }; // Якщо немає непарних вузлів, граф вже Ейлерів

    // Створення матриці найкоротших шляхів за допомогою Дейкстри
    vector<vector<int>> shortestPath(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
        vector<int> dist = dijkstra(i, g, n);

        for (int j = 0; j < n; ++j) {
            shortestPath[i][j] = dist[j];
        }
    }

    vector<vector<pair<int, int>>> allOddPairs;
    vector<pair<int, int>> currentPair;
    vector<bool> visited(oddNodes.size(), false);

    // Генерація всіх пар непарних вузлів
    generateOddPairs(oddNodes, 0, allOddPairs, currentPair, visited);

    vector<pair<int, int>> additionalEdges; // Додаткові ребра для Ейлерового циклу.
    int minDist = INT_MAX; // Мінімальна додаткова довжина

    // Знаходимо мінімальну відстань для парування непарних вузлів.
    for (auto j : allOddPairs) {
        int tans = 0;
        vector<pair<int, int>> tempEdges;

        for (auto i : j) {
            // Перевірка, чи існує шлях між парою вузлів i.first та i.second
            if (shortestPath[i.first][i.second] == INT_MAX) {
                tans = INT_MAX; // Якщо шляху немає, перериваємо
                break;
            }

            // Перевіряємо, чи існує прямий шлях між i.first та i.second
            bool directEdgeExists = false;
            int directEdgeWeight = INT_MAX;

            for (auto& neighbor : g[i.first]) {

                if (neighbor.first == i.second) {
                    directEdgeExists = true;
                    directEdgeWeight = neighbor.second;
                    break;
                }
            }

            // Якщо існує прямий шлях і його довжина відповідає мінімальній
            if (directEdgeExists && directEdgeWeight == shortestPath[i.first][i.second]) {
                tans += shortestPath[i.first][i.second];
                tempEdges.push_back({ i.first, i.second });
            }
            else {
                // Інакше шукаємо шлях через проміжні вершини за допомогою findVertexPath
                auto result = findVertexPath(i.first, i.second, g, tempEdges, shortestPath, n);

                if (result.first == INT_MAX) {
                    tans = INT_MAX; // Якщо шлях недосяжний, перериваємо
                    break;
                }

                tans += result.first;
            }
        }

        // Оновлення мінімальної додаткової дистанції
        if (tans < minDist) {
            minDist = tans;
            additionalEdges = tempEdges;
        }
    }


    if (minDist == INT_MAX)
        return { }; // Немає можливості побудувати Ейлерів цикл

    // Повертаємо загальну вагу і додаткові ребра для Ейлерового циклу
    return { additionalEdges };
}

// Функція для підрахунку ваги шляху
int Solution::calculateRouteWeight(const vector<pair<int, int>>& path, const vector<vector<int>>& edges) {
   
    int totalWeight = 0;

    for (const auto& edge : path) {

        for (const auto& originalEdge : edges) {

            if ((originalEdge[0] == edge.first && originalEdge[1] == edge.second) ||
                (originalEdge[0] == edge.second && originalEdge[1] == edge.first)) {
                
                totalWeight += originalEdge[2];

                break;
            }
        }
    }
    return totalWeight;
}
