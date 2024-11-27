#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <utility> // ��� std::pair
#include <limits> // ��� INT_MAX
#include <unordered_map> // ��� std::unordered_map
#include <queue> //��� ����� � �������� ��������

using namespace std;

class Solution {
public:

    // �������� �������� ��� ������ ������������ ����� �� ������� �� ��� ����� ������
    static vector<int> dijkstra(int src, const vector<vector<pair<int, int>>>& g, int n);

    // ��������� ��� �������� ��� ��� �������� ����� ����� (���������� �������)
    static void generateOddPairs(const vector<int>& oddNodes, int index,
        vector<vector<pair<int, int>>>& allOddPairs,
        vector<pair<int, int>>& currentPair,
        vector<bool>& visited);

    // ����� ������������ ����� �� ����� ��������� � ������������� �������� ������
    static pair<int, vector<pair<int, int>>> findVertexPath(
        int u, int v,
        const vector<vector<pair<int, int>>>& g,
        vector<pair<int, int>>& tempEdges,
        const vector<vector<int>>& shortestPath, int n);

    // ������� ������� ��� �������� �������� ����������� ���������
    static vector<pair<int, int>> chinesePostmanProblem(vector<vector<int>>& edges, int n);

    // ϳ�������� ���� �������� �� ����� ���� �����
    int calculateRouteWeight(const vector<pair<int, int>>& path, const vector<vector<int>>& edges);
};
#endif
