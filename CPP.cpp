// Back-end complete function Template for C++
#include "CPP.h"
#include <limits.h> // Для INT_MAX
#include <stack>
#include <unordered_map> // Для std::unordered_map
using namespace std;

// Функція для пошуку найкоротших відстаней між усіма парами вузлів з використанням алгоритму Флойда-Уоршалла.
vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n)
{
    // Ініціалізація матриці відстаней з безкінечністю.
    vector<vector<int>> d(n, vector<int>(n, INT_MAX));

    // Встановлюємо діагональні елементи в 0.
    for (int i = 0; i < n; i++)
        d[i][i] = 0;

    // Оновлюємо матрицю відстаней з прямими ребрами, що є в графі.
    for (int i = 0; i < n; i++)
    {
        for (auto j : g[i])
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

// Допоміжна функція для генерації всіх можливих пар непарних вузлів.
void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v)
{
    if (i == (int)o.size())
    {
        allOddPairs.push_back(t);
        return;
    }

    if (v[i])
    {
        f(o, i + 1, allOddPairs, t, v);
        return;
    }

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
    v[i] = false;
}

int Solution::chinesePostmanProblem(vector<vector<int>>& e, int n)
{
    if (n == 0)
        return -1;

    vector <int> o; // Array to store the odd nodes in the graph.

    vector<vector<pair<int, int>>> g(n); // Adjacency list representation of the graph.

    int s = 0; // Variable to store the sum of all edge weights in the graph.

    // Constructing the adjacency list of the graph and calculating the sum of edge weights.
    for (auto j : e)
    {
        s += j[2];
        g[j[0] - 1].push_back({ j[1] - 1, j[2] });
        g[j[1] - 1].push_back({ j[0] - 1, j[2] });
    }

    // Finding the odd nodes in the graph.
    for (int i = 0; i < n; i++)
    {
        if (g[i].size() % 2)
            o.push_back(i);
    }

    // If there are no odd nodes, the graph is already eulerian and the answer is the sum of all edge weights.
    if (o.size() == 0)
        return s;

    vector <vector<pair<int, int>>> allOddPairs; // Array to store all possible sets of odd node pairs.

    vector<pair<int, int>> t; // Temporary array to store a set of odd node pairs.

    vector<bool> vis(o.size(), false); // Using vector<bool> to keep track of which odd nodes have been paired.

    fill(vis.begin(), vis.end(), false); // Initializing the vis array to false.

    f(o, 0, allOddPairs, t, vis); // Generating all possible pairs of odd nodes.

    vector<vector<int>> shortestPath = floydWarshalls(g, n); // Calculating the shortest distances between all pairs of nodes in the graph.

    int ans = INT_MAX; // Variable to store the minimum sum of shortest path distances from odd node pairs.

    // Finding the minimum sum of shortest path distances from all odd node pairs.
    for (auto j : allOddPairs)
    {
        int tans = 0;
        for (auto i : j)
        {
            // If the shortest distance between a pair of odd nodes is infinity, it means the nodes are disconnected.
            if (shortestPath[i.first][i.second] == INT_MAX)
            {
                tans = INT_MAX;
                break;
            }

            // Updating the temporary answer with the sum of shortest distances between odd node pairs.
            tans += shortestPath[i.first][i.second];
        }

        // Updating the final answer with the minimum sum of shortest distances.
        ans = min(ans, tans);
    }

    // If the answer is still infinity, it means no eulerian tour is possible in the graph.
    // Return -1 in that case.
    if (ans == INT_MAX)
        return -1;

    // Return the sum of all edge weights along with the minimum sum of shortest distances between odd node pairs.
    return s + ans;
}
