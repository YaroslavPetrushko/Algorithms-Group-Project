#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <utility> // Äëÿ std::pair
#include <limits> // Äëÿ INT_MAX
#include <unordered_map> // Äëÿ std::unordered_map
#include <queue>
//#include <stack>
//#include <list>

using namespace std;

void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v);

vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n);

vector<int> dijkstra(int src, vector<vector<pair<int, int>>>& g, int n);
//vector<vector<int>> findOddVertexPaths(const vector<vector<pair<int, int>>>& g, const vector<int>& oddVertices, int n);

class Solution {
public:
	pair<int, vector<pair<int, int>>> findVertexPath(int u, int v, vector<vector<pair<int, int>>>& g, vector<pair<int, int>>& tempEdges, const vector<vector<int>>& shortestPath, int n);

	pair<int, vector<pair<int, int>>>chinesePostmanProblem(vector<vector<int>>& e, int n);
};
#endif
