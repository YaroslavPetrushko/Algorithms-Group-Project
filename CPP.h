#ifndef CPP_H // ������ �� ��������� ��������
#define CPP_H

#include <vector>
#include <utility> // ��� std::pair
using namespace std;

void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v);

vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n);

class Solution {
public:
    pair<int, vector<pair<int, int>>>  chinesePostmanProblem(vector<vector<int>>& e, int n);
};

#endif // CPP_H
