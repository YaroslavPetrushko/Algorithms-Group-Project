//���������� ��� �������� �������� ����������� ���������, 
// ���������� ��� ����������� �������� ������� �� ���������� �����
#include "Solution.h"
using namespace std;

//�������� �������� ��� ���������� ������������ ����� �� ���� �����
vector<int> Solution::dijkstra(int src, vector<vector<pair<int, int>>>& g, int n) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, src });
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[u]) continue;

        for (auto& neighbor : g[u]) {
            int v = neighbor.first, weight = neighbor.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

// ������� f ���������� ������ �� ������ ���� ��� �������� �����,
// �������� ��� ��������� ������ ���������.
void Solution::f(vector<int> o, int i, vector<vector<pair<int, int>>>& allOddPairs, vector<pair<int, int>> t, vector<bool>& v) {

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

// ������� ��� ������ ������������ ����� �� ����� ��������� ����� ������ �������
pair<int, vector<pair<int, int>>> Solution::findVertexPath(int u, int v, vector<vector<pair<int, int>>>&g, vector<pair<int, int>>&tempEdges, const vector<vector<int>>&shortestPath, int n) {
    int minPath = INT_MAX;
    vector<pair<int, int>> bestPath;

    for (int k = 0; k < n; ++k) {
        if (k != u && k != v && shortestPath[u][k] < INT_MAX && shortestPath[k][v] < INT_MAX) {
            int pathLength = shortestPath[u][k] + shortestPath[k][v];
            if (pathLength == shortestPath[u][v] && pathLength < minPath) {
                minPath = pathLength;
                bestPath = { {u, k}, {k, v} };
            }
        }
    }

    if (minPath < INT_MAX) {
        tempEdges.insert(tempEdges.end(), bestPath.begin(), bestPath.end());
    }

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
    int minDist = INT_MAX; // ̳������� ��������� �������

    // ��������� ������� ����������� ������ �� ��������� ��������
    vector<vector<int>> shortestPath(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; ++i) {
        vector<int> dist = dijkstra(i, g, n);
        for (int j = 0; j < n; ++j) {
            shortestPath[i][j] = dist[j];
        }
    }

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
            // ��������, �� ���� ���� �� ����� ����� i.first �� i.second
            if (shortestPath[i.first][i.second] == INT_MAX) {
                tans = INT_MAX; // ���� ����� ����, ����������
                break;
            }

            // ����������, �� ���� ������ ���� �� i.first �� i.second
            bool directEdgeExists = false;
            int directEdgeWeight = INT_MAX;
            for (auto& neighbor : g[i.first]) {
                if (neighbor.first == i.second) {
                    directEdgeExists = true;
                    directEdgeWeight = neighbor.second;
                    break;
                }
            }

            // ���� ���� ������ ���� � ���� ������� ������� ��������
            if (directEdgeExists && directEdgeWeight == shortestPath[i.first][i.second]) {
                tans += shortestPath[i.first][i.second];
                tempEdges.push_back({ i.first, i.second });
            }
            else {
                // ������ ������ ���� ����� ������ ������� �� ��������� findVertexPath
                auto result = findVertexPath(i.first, i.second, g, tempEdges, shortestPath, n);
                if (result.first == INT_MAX) {
                    tans = INT_MAX; // ���� ���� ����������, ����������
                    break;
                }
                tans += result.first;
            }
        }

        // ��������� �������� ��������� ���������
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
