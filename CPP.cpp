// Back-end complete function Template for C++
#include "CPP.h"
#include <limits.h> // ��� INT_MAX
#include <stack>
#include <unordered_map> // ��� std::unordered_map
using namespace std;

// ������� ��� ������ ����������� �������� �� ���� ������ ����� � ������������� ��������� ������-��������.
vector<vector<int>> floydWarshalls(vector<vector<pair<int, int>>>& g, int n)
{
    // ����������� ������� �������� � �����������.
    vector<vector<int>> d(n, vector<int>(n, INT_MAX));

    // ������������ ��������� �������� � 0.
    for (int i = 0; i < n; i++)
        d[i][i] = 0;

    // ��������� ������� �������� � ������� �������, �� � � �����.
    for (int i = 0; i < n; i++)
    {
        for (auto j : g[i])
            d[i][j.first] = j.second;
    }

    // ���������� ��������� ������ �� ��������� ��������� ������-��������.
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

    // ��������� ������� ����������� ��������.
    return d;
}

// �������� ������� ��� ��������� ��� �������� ��� �������� �����.
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

pair<int, vector<pair<int, int>>> Solution::chinesePostmanProblem(vector<vector<int>>& e, int n) {
    if (n == 0)
        return { -1, {} };

    vector<int> o; // ������ ��� ���������� ����� � �������� ��������.
    vector<vector<pair<int, int>>> g(n); // ������ ���������� �����.
    int s = 0; // ���� ��� ��� ����� � �����.

    // ��������� ������ ���������� ����� �� ���������� ���� ���.
    for (auto j : e) {
        s += j[2];
        g[j[0] - 1].push_back({ j[1] - 1, j[2] });
        g[j[1] - 1].push_back({ j[0] - 1, j[2] });
    }

    // ��������� ����� � �������� ��������.
    for (int i = 0; i < n; i++) {
        if (g[i].size() % 2)
            o.push_back(i);
    }

    if (o.size() == 0)
        return { s, {} }; // ���� ���� �������� �����, ���� ��� ������.

    vector<vector<int>> shortestPath = floydWarshalls(g, n);
    vector<pair<int, int>> additionalEdges;

    // ��������� ��� �������� ��� �������� ����� � ����������� �������� ����.
    vector<vector<pair<int, int>>> allOddPairs;
    vector<pair<int, int>> t;
    vector<bool> vis(o.size(), false);
    f(o, 0, allOddPairs, t, vis);

    int minDist = INT_MAX;
    for (auto j : allOddPairs) {
        int tans = 0;
        vector<pair<int, int>> tempEdges;
        for (auto i : j) {
            if (shortestPath[i.first][i.second] == INT_MAX) {
                tans = INT_MAX;
                break;
            }
            tans += shortestPath[i.first][i.second];
            tempEdges.push_back({ i.first, i.second });
        }
        if (tans < minDist) {
            minDist = tans;
            additionalEdges = tempEdges;
        }
    }

    if (minDist == INT_MAX)
        return { -1, {} }; // ���� ��������� ���������� ������ ����.

    // ��������� �������� ���� � �������� ����� ��� ���������� �����.
    return { s + minDist, additionalEdges };
}
