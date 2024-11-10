//Функціонал для вирішення проблеми китайського листоноші, 
// здебільшого для знаходження мінімальної довжини та додаткових ребер
#include "Solution.h"
using namespace std;

// Функція floydWarshalls реалізує адаптований алгоритм Флойда-Уоршалла
// для знаходження найкоротших відстаней між усіма парами суміжних вершин в графі.
vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n) {
    // Ініціалізація матриці відстаней з безкінечністю (INT_MAX).
    vector<vector<int>> d(n, vector<int>(n, INT_MAX));

    // Встановлюємо нулі для діагоналі матриці, оскільки шлях до самої себе дорівнює 0.
    for (int i = 0; i < n; i++)
        d[i][i] = 0;

    // Призначення початкових ваг між суміжними вершинами.
    for (int i = 0; i < n; i++) {
        for (auto& j : g[i]) {
            d[i][j.first] = j.second;  // Встановлення ваги між суміжними вершинами.
        }
    }

    // Повертаємо матрицю найкоротших відстаней.
    return d;
}


// Функція f рекурсивно генерує всі можливі пари для непарних вузлів,
// необхідні для китайської задачі листоноші.
void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v) {
    
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

// Функція findShortestPathThroughCommonVertex шукає найкоротший шлях між двома
// вершинами через спільну проміжну вершину, якщо прямий шлях відсутній.
pair<int, vector<pair<int, int>>> Solution::findShortestPathThroughCommonVertex(int u, int v, const vector<vector<int>>& shortestPath, int n) {
    int minPath = INT_MAX;
    vector<pair<int, int>> bestPath;

    for (int k = 0; k < n; ++k) {
        // Перевіряємо, чи існує шлях від u до k і від k до v
        if (k != u && k != v && shortestPath[u][k] < INT_MAX && shortestPath[k][v] < INT_MAX) {
            int pathLength = shortestPath[u][k] + shortestPath[k][v];
            if (pathLength < minPath) {
                minPath = pathLength;
                bestPath = { {u, k}, {k, v} };
            }
        }
    }

    // Повертаємо числове значення найкоротшого шляху між двома вершинами та вектор вершин
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
    vector<vector<int>> shortestPath = floydWarshalls(g, n); // Знаходимо найкоротші шляхи між парами вершин.
    int minDist = INT_MAX; // Мінімальна додаткова довжина

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
            // Якщо прямий шлях відсутній, шукаємо шлях через проміжну вершину.
            if (shortestPath[i.first][i.second] == INT_MAX || shortestPath[i.first][i.second] == 0) {
                pair<int, vector<pair<int, int>>> result = findShortestPathThroughCommonVertex(i.first, i.second, shortestPath, n);
                int pathLength = result.first;
                vector<pair<int, int>> pathEdges = result.second;

                // Перевіряємо, чи знайдено шлях через спільну вершину
                if (pathLength == INT_MAX) {
                    tans = INT_MAX;
                    break;
                }

                tans += pathLength;
                tempEdges.insert(tempEdges.end(), pathEdges.begin(), pathEdges.end());
            }
            else {
                // Якщо прямий шлях існує, додаємо його
                tans += shortestPath[i.first][i.second];
                tempEdges.push_back({ i.first, i.second });
            }
        }

        // Оновлюємо мінімальну додаткову дистанцію, якщо знайдено меншу вартість
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