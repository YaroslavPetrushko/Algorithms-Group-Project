#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string.h>
#include <vector>

using namespace std;

// ����, �� ���������� ����
class Graph {
    int V; // ʳ������ ������
    list<int>* adj; // ��������� ����� ������ ��������

public:
    // ����������� �� ����������
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    // ������� ��� ��������� �� ��������� ����� �����
    void addEdge(int u, int v);
    void rmvEdge(int u, int v);

    // ������� ��� ��������� �����
    void printGraph(const vector<vector<int>>& e, int n);

    //������� ��� ������ ����� �� ����� CPP_output.txt
    void writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath);

    //������� ��� ������ ���������� ����� �� ����� CPP_extend.txt
    void writeExtendedPathToFile(const vector<vector<int>>& edges, 
        const vector<pair<int, int>>& newPath,
        const vector<pair<int, int>>& additionalEdges);

    // ������ ��� ���������� ���������� �����
    vector<pair<int, int>> getEulerPath(const vector<pair<int, int>>& additionalEdges);
    void getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath);

    //������ ��� ��������� ���������� ����� � �������
    void printEulerTour(const vector<pair<int, int>>& previousPath);
    void printEulerExtend(const vector<pair<int, int>>& previousPath,
        const vector<pair<int, int>>& additionalEdges,
        const vector<pair<int, int>>& newPath);

    //��������� �������� ���� �����
    int getTotalWeight(const vector<vector<int>>& edges);

    // ������� �� ������� ������� �������� ������
    int DFSCount(int v, bool visited[]);

    // �������� ������� ��� ��������, �� � ����� u-v ������
    // �� �� � ��������� ������ � ���������� �����
    bool edgeExists(int u, int v);
    bool isValidNextEdge(int u, int v);

private:
    vector<pair<int, int>> e; // ������ ��� ��������� ����� �����
};
