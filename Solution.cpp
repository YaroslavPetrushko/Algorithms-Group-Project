// Back-end complete function Template for C++
#include "Solution.h"
#include <limits.h> // ��� INT_MAX
#include <stack>
#include <unordered_map> // ��� std::unordered_map
using namespace std;

// ������� ��� ������ ����������� �������� �� ���� ������ ����� � ������������� ��������� ������-��������,
// � ����������, �� ���������� ����������� ������ ���������� ����� ��� ������� ������.
vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n) {
    // ����������� ������� �������� � ����������� (INT_MAX).
    vector<vector<int>> d(n, vector<int>(n, INT_MAX));

    // ������������ ��������� �������� � 0 (������� ����� �� ���� ����).
    for (int i = 0; i < n; i++)
        d[i][i] = 0;

    //³������ �� ��������� ����������� ����� �� ����� �������� �����
    // ��������� ������� �������� ��� ������� ������ �� ����� �����, �� � � �����.
    for (int i = 0; i < n; i++) {
        for (auto& j : g[i]) {
            d[i][j.first] = j.second;  // ������������ ���� �� �������� ���������
        }
    }

    ////������ �������������� ���������� �����
    //// ���������� ���������� ������ ���� ��� �������� ����� �� ��������� ��������� ������-��������.
    //for (int k = 0; k < n; k++) {
    //    for (int i = 0; i < n; i++) {
    //        for (int j = 0; j < n; j++) {
    //            // �������� ���������� ����� ��� ��� ������, �� � ��������
    //            if (d[i][k] != INT_MAX && d[k][j] != INT_MAX && i != j) {
    //                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    //            }
    //        }
    //    }
    //}

    // ��������� ������� ����������� ��������.
    return d;
}


// �������� ������� ��� ��������� ��� �������� ��� �������� �����.
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

    vector<int> oddNodes; // ����� ��� ���������� ����� � �������� ��������
    vector<vector<pair<int, int>>> g(n); // ������ ����� �����
    int totalWeight = 0; // ���� ��� ��� ����� � �����

    // ��������� ������ ���������� ����� �� ���������� ���� ���
    for (auto j : e) {
        totalWeight += j[2];
        g[j[0] - 1].push_back({ j[1] - 1, j[2] });
        g[j[1] - 1].push_back({ j[0] - 1, j[2] });
    }

    // ��������� ����� � �������� ��������
    for (int i = 0; i < n; i++) {
        if (g[i].size() % 2)
            oddNodes.push_back(i);
    }

    if (oddNodes.size() == 0)
        return { totalWeight, {} }; // ���� ���� �������� �����, ���� ��� ������

    vector<pair<int, int>> additionalEdges; // ������ ���������� �����
    vector<vector<int>> shortestPath = floydWarshalls(g, n); // ��������� ���������� ����� �� ���� ������ ������
    int minDist = INT_MAX; // ̳������� ��������� ���������

    // �������� �� ������ ���� �������� ������ � ��������� �������� ����
    vector<vector<pair<int, int>>> allOddPairs;
    vector<pair<int, int>> t;
    vector<bool> vis(oddNodes.size(), false);
    f(oddNodes, 0, allOddPairs, t, vis);

    // ���������� �� ������ ���� �������� ������
    for (auto j : allOddPairs) {
        int tans = 0;
        vector<pair<int, int>> tempEdges;

        for (auto i : j) {
            // ���� ������� ����� ���� ��� �� ������� 0, ������ ���� ����� ������ �������
            if (shortestPath[i.first][i.second] == INT_MAX || shortestPath[i.first][i.second] == 0) {
                pair<int, vector<pair<int, int>>> result = findShortestPathThroughCommonVertex(i.first, i.second, shortestPath, n);
                int pathLength = result.first;
                vector<pair<int, int>> pathEdges = result.second;

                // ����������, �� �������� ���� ����� ������ �������
                if (pathLength == INT_MAX) {
                    tans = INT_MAX;
                    break;
                }

                tans += pathLength;
                tempEdges.insert(tempEdges.end(), pathEdges.begin(), pathEdges.end());
            }
            else {
                // ���� ������ ���� ����, ������ ����
                tans += shortestPath[i.first][i.second];
                tempEdges.push_back({ i.first, i.second });
            }
        }

        // ��������� �������� ��������� ���������, ���� �������� ����� �������
        if (tans < minDist) {
            minDist = tans;
            additionalEdges = tempEdges;
        }
    }

    if (minDist == INT_MAX)
        return { -1, {} }; // ���� ��������� ���������� ������ ����

    // ��������� �������� ���� � �������� ����� ��� ���������� �����
    return { totalWeight + minDist, additionalEdges };
}

// ������� ��� ����������� ������������ ����� �� ����� ��������� ����� ����� �������
pair<int, vector<pair<int, int>>> Solution::findShortestPathThroughCommonVertex(int u, int v, const vector<vector<int>>& shortestPath, int n) {
    int minPath = INT_MAX;
    vector<pair<int, int>> bestPath;

    for (int k = 0; k < n; ++k) {
        // ����������, �� ���� ���� �� u �� k � �� k �� v
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
