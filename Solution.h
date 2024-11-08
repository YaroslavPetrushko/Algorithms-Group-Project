#ifndef SOLUTION_H // Захист від множинних включень
#define SOLUTION_H

#include <vector>
#include <list>
#include <utility> // Для std::pair
using namespace std;

void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v);

vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n);

class Solution {
public:
	pair<int, vector<pair<int, int>>>chinesePostmanProblem(vector<vector<int>>& e, int n);
	pair<int, vector<pair<int, int>>> findShortestPathThroughCommonVertex(int u, int v, const vector<vector<int>>& shortestPath, int n);

};
#endif // SOLUTION_H
