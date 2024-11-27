#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <utility> // Для std::pair
#include <limits> // Для INT_MAX
#include <unordered_map> // Для std::unordered_map
#include <queue> //Для черги в алгоритмі Дейкстри

using namespace std;

class Solution {
public:

    // Алгоритм Дейкстри для пошуку найкоротшого шляху від джерела до всіх інших вершин
    static vector<int> dijkstra(int src, const vector<vector<pair<int, int>>>& g, int n);

    // Генерація всіх можливих пар для непарних вузлів графу (рекурсивна функція)
    static void generateOddPairs(const vector<int>& oddNodes, int index,
        vector<vector<pair<int, int>>>& allOddPairs,
        vector<pair<int, int>>& currentPair,
        vector<bool>& visited);

    // Пошук найкоротшого шляху між двома вершинами з використанням проміжних вершин
    static pair<int, vector<pair<int, int>>> findVertexPath(
        int u, int v,
        const vector<vector<pair<int, int>>>& g,
        vector<pair<int, int>>& tempEdges,
        const vector<vector<int>>& shortestPath, int n);

    // Основна функція для вирішення проблеми китайського листоноші
    static vector<pair<int, int>> chinesePostmanProblem(vector<vector<int>>& edges, int n);

    // Підрахунок ваги маршруту на основі його ребер
    int calculateRouteWeight(const vector<pair<int, int>>& path, const vector<vector<int>>& edges);
};
#endif
