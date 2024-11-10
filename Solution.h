#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <utility> // Для std::pair
#include <limits.h> // Для INT_MAX
#include <unordered_map> // Для std::unordered_map
//#include <stack>
//#include <list>

using namespace std;

void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v);

vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n);

class Solution {
public:
	pair<int, vector<pair<int, int>>> findShortestPathThroughCommonVertex(int u, int v, const vector<vector<int>>& shortestPath, int n);

	pair<int, vector<pair<int, int>>>chinesePostmanProblem(vector<vector<int>>& e, int n);
};
#endif
