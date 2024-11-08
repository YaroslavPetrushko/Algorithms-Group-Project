#ifndef CPP_H // Захист від множинних включень
#define CPP_H

#include <vector>
#include <list>
#include <utility> // Для std::pair
using namespace std;

class Solution {
public:
    pair<int, vector<int>> ChinesePostmanProblem(const vector<vector<int>>& e, int n);

private:
    void generatePairs(const vector<int>& oddVertices, int index, vector<vector<pair<int,
        int>>>& allPairs, vector<pair<int, int>>& current,vector<bool>& visited);

    vector<vector<int>> floydWarshalls(const vector<vector<pair<int, int>>>& graph, int n);
    list<int> findEulerianCycle(vector<vector<pair<int, int>>>& graph, int n);

};
#endif // CPP_H
