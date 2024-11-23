#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

// ����, �� ���������� ����
class Graph {
    int V; // ʳ������ ������
    list<int>* adj; // ��������� ����� ������ ��������
    map<int, int> vertexMapping;       // ³����������: �������� ������ -> ����� ������
    map<int, int> reverseVertexMapping; // ³����������: ����� ������ -> �������� ������

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

    // ������� ��� ������ � ��������������
    vector<vector<int>> renumberGraph(const vector<vector<int>>& edges);
    vector<pair<int, int>> revertEulerPath(const vector<pair<int, int>>& eulerPath);

    // ������� ��� �������� ����� ����� ������������
    vector<vector<int>> inputGraph(int& n);

    // ������� ��� ��������� �����
    void printGraph(const vector<vector<int>>& e, int n);

    //������� ��� ������ ����� �� ����� CPP_output.txt
    void writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath, string filename);

    // ������ ��� ���������� ���������� �����
    vector<pair<int, int>> getEulerPath(const vector<pair<int, int>>& additionalEdges);
    void getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath);

    //����� ��� ��������� ���������� ����� � �������
    void printEulerTour(const vector<pair<int, int>>& previousPath);

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
