//���������� ��� �������� �������� ����������� ���������, 
// ���������� ��� ����������� �������� ������� �� ���������� �����
#include "Solution.h"
using namespace std;

// ������� floydWarshalls ������ ����������� �������� ������-��������
// ��� ����������� ����������� �������� �� ���� ������ ������� ������ � �����.
vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n) {
    // ����������� ������� �������� � ����������� (INT_MAX).
    vector<vector<int>> d(n, vector<int>(n, INT_MAX));

    // ������������ ��� ��� ������� �������, ������� ���� �� ���� ���� ������� 0.
    for (int i = 0; i < n; i++)
        d[i][i] = 0;

    // ����������� ���������� ��� �� �������� ���������.
    for (int i = 0; i < n; i++) {
        for (auto& j : g[i]) {
            d[i][j.first] = j.second;  // ������������ ���� �� �������� ���������.
        }
    }

    // ��������� ������� ����������� ��������.
    return d;
}


// ������� f ���������� ������ �� ������ ���� ��� �������� �����,
// �������� ��� ��������� ������ ���������.
void f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v) {
    
    if (i == (int)o.size()) { // ������� �������: �� ������ ����� �'������ � ����
        allOddPairs.push_back(t);
        return;
    }

    if (v[i]) { // ���������� �� ����� ��� 璺�����
        f(o, i + 1, allOddPairs, t, v);
        return;
    }

    // ���������� �������� ����� �������� ����� �� ��������� ��� ����.
    v[i] = true;

    for (int j = 0; j < (int)o.size(); j++) {
        if (!v[j]) { // ���������� ����� ��� ����
            v[j] = true;
            t.push_back({ o[i], o[j] });
            f(o, i + 1, allOddPairs, t, v);
            t.pop_back(); // ���������� �� ������������ �����
            v[j] = false;
        }
    }

    v[i] = false;
}

// ������� findShortestPathThroughCommonVertex ���� ����������� ���� �� �����
// ��������� ����� ������ ������� �������, ���� ������ ���� �������.
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

    // ��������� ������� �������� ������������ ����� �� ����� ��������� �� ������ ������
    return { minPath, bestPath };
}

// ������� ������� ��� ����'������ ��������� ������ ���������. ���� �������,
// �� �������� ����� ������� ������ �� ����� ��� �������� ���������� �����.
pair<int, vector<pair<int, int>>> Solution::chinesePostmanProblem(vector<vector<int>>& e, int n) {
    if (n == 0) return { -1, {} }; // ��������� -1, ���� ���� �������.

    vector<int> oddNodes; // ����� ��� ���������� ����� � �������� ��������
    vector<vector<pair<int, int>>> g(n); // ������ ����� �����
    int totalWeight = 0; // ���� ������� ��� ����� � �����

    // ��������� ������ ���������� ����� �� ���������� �������
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

    vector<pair<int, int>> additionalEdges; // �������� ����� ��� ���������� �����.
    vector<vector<int>> shortestPath = floydWarshalls(g, n); // ��������� ���������� ����� �� ������ ������.
    int minDist = INT_MAX; // ̳������� ��������� �������

    // �������� �� ������ ���� �������� ������
    vector<vector<pair<int, int>>> allOddPairs;
    vector<pair<int, int>> t;
    vector<bool> vis(oddNodes.size(), false);
    f(oddNodes, 0, allOddPairs, t, vis);

    // ��������� �������� ������� ��� ��������� �������� �����.
    for (auto j : allOddPairs) {
        int tans = 0;
        vector<pair<int, int>> tempEdges;

        for (auto i : j) {
            // ���� ������ ���� �������, ������ ���� ����� ������� �������.
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