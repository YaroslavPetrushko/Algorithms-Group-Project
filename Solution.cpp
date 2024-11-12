//Функціонал для вирішення проблеми китайського листоноші, 
// здебільшого для знаходження мінімальної довжини та додаткових ребер
#include "Solution.h"
using namespace std;

//Алгоритм Дейсктри для визначення найкоротшого шлязу від однієї точки
vector<int> Solution::dijkstra(int src, vector<vector<pair<int, int>>>& g, int n) {
    vector<int> dist(n, INT_MAX);
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

// Функція f рекурсивно генерує всі можливі пари для непарних вузлів,
// необхідні для китайської задачі листоноші.
void Solution::f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v) {

    if (i == (int)o.size()) { // Базовий випадок: всі непарні вузли з'єднано в пари
        allOddPairs.push_back(t);
        return;
    }

    if (v[i]) { // Пропускаємо що вузли вже з’єднано
        f(o, i + 1, allOddPairs, t, v);
        return;
    }

    // Рекурсивно вибираємо кожен непарний вузол як стартовий для пари.
    v[i] = true;

    for (int j = 0; j < (int)o.size(); j++) {
        if (!v[j]) { // Перевіряємо вузол для пари
            v[j] = true;
            t.push_back({ o[i], o[j] });
            f(o, i + 1, allOddPairs, t, v);
            t.pop_back(); // Повернення до попереднього стану
            v[j] = false;
        }
    }

    v[i] = false;
}

// Функція для пошуку найкоротшого шляху між двома вершинами через спільну вершину
pair<int, vector<pair<int, int>>> Solution::findVertexPath(int u, int v, vector<vector<pair<int, int>>>&g, vector<pair<int, int>>&tempEdges, const vector<vector<int>>&shortestPath, int n) {
    int minPath = INT_MAX;
    vector<pair<int, int>> bestPath;

    for (int k = 0; k < n; ++k) {
        if (k != u && k != v && shortestPath[u][k] < INT_MAX && shortestPath[k][v] < INT_MAX) {
            int pathLength = shortestPath[u][k] + shortestPath[k][v];
            if (pathLength == shortestPath[u][v] && pathLength < minPath) {
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

// Основна функція для розв'язання китайської задачі листоноші. Вона визначає,
// які додаткові ребра потрібно додати до графа для побудови Ейлерового циклу.
pair<int, vector<pair<int, int>>> Solution::chinesePostmanProblem(vector<vector<int>>& e, int n) {
    if (n == 0) return { -1, {} }; // Повертаємо -1, якщо граф порожній.

    vector<int> oddNodes; // Масив для збереження вузлів з непарним степенем
    vector<vector<pair<int, int>>> g(n); // Список ребер графу
    int totalWeight = 0; // Сума довжини усіх ребер у графі

    // Створюємо список суміжностей графу та обчислюємо довжину
    for (auto j : e) {
        totalWeight += j[2];
        g[j[0] - 1].push_back({ j[1] - 1, j[2] });
        g[j[1] - 1].push_back({ j[0] - 1, j[2] });
    }

    // Знаходимо вузли з непарним степенем
    for (int i = 0; i < n; i++) {
        if (g[i].size() % 2)
            oddNodes.push_back(i);
    }

    if (oddNodes.size() == 0)
        return { totalWeight, {} }; // Якщо немає непарних вузлів, граф вже Ейлерів

    vector<pair<int, int>> additionalEdges; // Додаткові ребра для Ейлерового циклу.
    int minDist = INT_MAX; // Мінімальна додаткова довжина

    // Створення матриці найкоротших шляхів за допомогою Дейкстри
    vector<vector<int>> shortestPath(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; ++i) {
        vector<int> dist = dijkstra(i, g, n);
        for (int j = 0; j < n; ++j) {
            shortestPath[i][j] = dist[j];
        }
    }

    // Генеруємо всі можливі пари непарних вершин
    vector<vector<pair<int, int>>> allOddPairs;
    vector<pair<int, int>> t;
    vector<bool> vis(oddNodes.size(), false);
    f(oddNodes, 0, allOddPairs, t, vis);

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
        return { -1, {} }; // Немає можливості побудувати Ейлерів цикл

    // Повертаємо загальну вагу і додаткові ребра для Ейлерового циклу
    return { totalWeight + minDist, additionalEdges };
}
