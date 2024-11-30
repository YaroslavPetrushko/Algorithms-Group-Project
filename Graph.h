#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <string>
#include <vector>
#include <map>
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
    Graph(int V) ;
    ~Graph();

    // ������� ��� ��������� �� ��������� ����� �����
    void addEdge(int u, int v);
    void rmvEdge(int u, int v);

    // ������� ��� ������ � �������������� ������ �����
    pair<int, vector<vector<int>>> renumberGraph(const vector<vector<int>>& edges, int startPoint);
    vector<pair<int, int>> revertEulerPath(const vector<pair<int, int>>& eulerPath);

    // ������� ��� ��������� �����
    void printGraph(const vector<vector<int>>& e, int n, int startPoint);

    //������� ��� ������ ����� �� ����� CPP_output.txt
    void writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath, int weight,int startPoint, string filename);

    // ������ ��� ���������� ���������� �����
    vector<pair<int, int>> getEulerPath(const vector<pair<int, int>>& additionalEdges, int startPoint);
    void getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath);

    //����� ��� ��������� ���������� ����� � �������
    void printEulerTour(const vector<pair<int, int>>& previousPath);

    // ������� �� ������� ������� �������� ������
    int DFSCount(int v, bool visited[]);

    // �������� ������� ��� ��������, �� � ����� u-v ������
    // �� �� � ��������� ������ � ���������� �����
    bool edgeExists(int u, int v);
    bool isValidNextEdge(int u, int v);

private:
    vector<pair<int, int>> e; // ������ ��� ��������� ����� �����
};
