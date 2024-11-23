#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <utility> // Äëÿ std::pair
#include <limits> // Äëÿ INT_MAX
#include <unordered_map> // Äëÿ std::unordered_map
#include <queue>

using namespace std;

class Solution {
public:

	static vector<int> dijkstra(int src, vector<vector<pair<int, int>>>& g, int n);

	static void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v);

	static pair<int, vector<pair<int, int>>> findVertexPath(int u, int v, vector<vector<pair<int, int>>>& g, vector<pair<int, int>>& tempEdges, const vector<vector<int>>& shortestPath, int n);

	static pair<int, vector<pair<int, int>>>chinesePostmanProblem(vector<vector<int>>& e, int n);
};
#endif
