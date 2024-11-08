// Back-end complete function Template for C++
#include "Solution.h"
#include <limits.h> // Для INT_MAX
#include <stack>
#include <unordered_map> // Для std::unordered_map
using namespace std;

// Функція для пошуку найкоротших відстаней між усіма парами вузлів з використанням алгоритму Флойда-Уоршалла,
// з обмеженням, що обчислення найкоротших шляхів виконується тільки для суміжних вершин.
vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n) {
    // Ініціалізація матриці відстаней з безкінечністю (INT_MAX).
    vector<vector<int>> d(n, vector<int>(n, INT_MAX));

    // Встановлюємо діагональні елементи в 0 (довжина шляху до самої себе).
    for (int i = 0; i < n; i++)
        d[i][i] = 0;

    //Відповідає за початкове призначення даних на основі існуючих ребер
    // Оновлюємо матрицю відстаней для суміжних вершин на основі ребер, що є в графі.
    for (int i = 0; i < n; i++) {
        for (auto& j : g[i]) {
            d[i][j.first] = j.second;  // Встановлюємо вагу між суміжними вершинами
        }
    }

    ////Довнює використовуючи сполучення ребер
    //// Обчислюємо найкоротші відстані лише для існуючих ребер за допомогою алгоритму Флойда-Уоршалла.
    //for (int k = 0; k < n; k++) {
    //    for (int i = 0; i < n; i++) {
    //        for (int j = 0; j < n; j++) {
    //            // Виконуємо обчислення тільки для тих вершин, які є суміжними
    //            if (d[i][k] != INT_MAX && d[k][j] != INT_MAX && i != j) {
    //                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    //            }
    //        }
    //    }
    //}

    // Повертаємо матрицю найкоротших відстаней.
    return d;
}


// Допоміжна функція для генерації всіх можливих пар непарних вузлів.
void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v)
{
    //Base case: If all odd nodes have been considered, add the pair set to the resulting array.
    if (i == (int)o.size())
    {
        allOddPairs.push_back(t);
        return;
    }

    //If the current odd node has already been paired, move to the next node.
    if (v[i])
    {
        f(o, i + 1, allOddPairs, t, v);
        return;
    }

    //Choose the currentodd node as the start node and pair it with all the remaining odd nodes.
    v[i] = true;
    for (int j = 0; j < (int)o.size(); j++)
    {
        if (!v[j])
        {
            v[j] = true;
            t.push_back({ o[i], o[j] });
            f(o, i + 1, allOddPairs, t, v);
            t.pop_back();
            v[j] = false;
        }
    }

    //Reset the flag for the current odd node.
    v[i] = false;
}

pair<int, vector<pair<int, int>>> Solution::chinesePostmanProblem(vector<vector<int>>& e, int n) {
    if (n == 0)
        return { -1, {} };

    vector<int> oddNodes; // Масив для збереження вузлів з непарною степенем
    vector<vector<pair<int, int>>> g(n); // Список ребер графу
    int totalWeight = 0; // Сума ваг усіх ребер у графі

    // Створюємо список суміжностей графу та обчислюємо суму ваг
    for (auto j : e) {
        totalWeight += j[2];
        g[j[0] - 1].push_back({ j[1] - 1, j[2] });
        g[j[1] - 1].push_back({ j[0] - 1, j[2] });
    }

    // Знаходимо вузли з непарною степенем
    for (int i = 0; i < n; i++) {
        if (g[i].size() % 2)
            oddNodes.push_back(i);
    }

    if (oddNodes.size() == 0)
        return { totalWeight, {} }; // Якщо немає непарних вузлів, граф вже Ейлерів

    vector<pair<int, int>> additionalEdges; // Вектор додаткових ребер
    vector<vector<int>> shortestPath = floydWarshalls(g, n); // Знаходимо найкоротші шляхи між усіма парами вершин
    int minDist = INT_MAX; // Мінімальна додаткова дистанція

    // Генеруємо усі можливі пари непарних вершин і знаходимо мінімальну вагу
    vector<vector<pair<int, int>>> allOddPairs;
    vector<pair<int, int>> t;
    vector<bool> vis(oddNodes.size(), false);
    f(oddNodes, 0, allOddPairs, t, vis);

    // Перебираємо всі можливі пари непарних вершин
    for (auto j : allOddPairs) {
        int tans = 0;
        vector<pair<int, int>> tempEdges;

        for (auto i : j) {
            // Якщо прямого шляху немає або він дорівнює 0, шукаємо шлях через спільну вершину
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

// Функція для знаходження найкоротшого шляху між двома вершинами через спільні вершини
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
    return { minPath, bestPath };
}
