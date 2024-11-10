//���������� ��� �����䳿 � ������, (��������/���������)
// �� ����������� � ��������� ���������� �����
#include "Graph.h"
using namespace std;

// ������� ��� ������������ �������� ������� � �������
char indexToChar(int index) {
    return 'A' + index; // ���������� 0 � 'A', 1 � 'B', � �.�.
}

// ������� ��� ���������� ����� �� �����������
vector<vector<int>> inputGraph(int& n) {
    cout << "������ ������� ������: ";
    cin >> n;
    int edges;
    cout << "������ ������� �����: ";
    cin >> edges;

    vector<vector<int>> e;
    cout << "������ ����� � ������ '������� ����� ����':\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({ u, v, w });
    }
    return e;
}

// ������� ��� ��������� �����
void printGraph(const vector<vector<int>>& e, int n) {
    cout << "��� �����.\n";
    cout << "ʳ������ ������: " << n << endl;
    cout << "�����:\n";
    for (const auto& edge : e) {
        cout << "������� " << indexToChar(edge[0] - 1) << " - ������� "
            << indexToChar(edge[1] - 1) << ": ���� " << edge[2] << endl;
    }
}


// ������� ��� ������������ ��������� ����� 1
vector<vector<int>> getTemplateData1(int& n) {
    n = 5; // ʳ������ �����
    return {
        {1, 2, 100}, // A - B: 100
        {1, 3, 150}, // A - C: 150
        {2, 3, 120}, // B - C: 120
        {2, 4, 200}, // B - D: 200
        {3, 4, 180}, // C - D: 180
        {3, 5, 160}, // C - E: 160
        {4, 5, 140}  // D - E: 140
    };
}

// ������� ��� ������������ ��������� ����� 2
vector<vector<int>> getTemplateData2(int& n) {
    n = 13; // ʳ������ �����
    return {
        {1, 2, 1300}, // A - B: 1300
        {1, 10, 550}, // A - J: 550
        {2, 3, 350},  // B - C: 350
        {3, 4, 150},  // C - D: 150
        {3, 11, 500}, // C - K: 500
        {4, 5, 500},  // D - E: 500
        {4, 12, 350}, // D - L: 350
        {5, 6, 350},  // E - F: 350
        {6, 7, 350},  // F - G: 350
        {6, 13, 240}, // F - M: 240
        {7, 8, 260},  // G - H: 260
        {8, 9, 490},  // H - I: 490
        {8, 13, 350}, // H - M: 350
        {9, 10, 260}, // I - J: 260
        {9, 11, 350}, // I - K: 350
        {11, 12, 150},// K - L: 150
        {12, 13, 210} // L - M: 210
    };
}

// ����� getEulerPath ������� ������ ���� ��� �����.
vector<pair<int, int>> Graph::getEulerPath(const vector<pair<int, int>>& additionalEdges) {
    // ������ �������� ����� � ����
    for (const auto& edge : additionalEdges) {
        addEdge(edge.first, edge.second);
    }

    // ��������� ������� � �������� ��������, ���� ���� �
    int u = 0;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() & 1) {
            u = i;
            break;
        }
    }

    vector<pair<int, int>> eulerPath;
    getEulerPathUtil(u, eulerPath);  // ��������� �������� ������� ��� ��������� �����
    
    // ��������� ��������� ����
    return eulerPath;
}

// ��������� ����� getEulerPathUtil ��� �������� ���������� �����.
void Graph::getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath) {
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (v != -1 && isValidNextEdge(u, v)) {
            eulerPath.push_back({ u, v });  // ������ ���� (u, v) �� �����
            rmvEdge(u, v);
            getEulerPathUtil(v, eulerPath);  // ���������� ��������� ��� �������� �������
        }
    }
}

// ����� printEulerTour �������� ������ ������� �� �����.
void Graph::printEulerTour(const vector<pair<int, int>>& previousPath) {
    cout << "��������� ������� :\n";
    for (const auto& edge : previousPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";  // �������� ����, ��� ���������, �� �� �������
    }
    cout << endl;
}

// ����� printEulerExtend �������� ��������� ������ ���� �� �����.
void Graph::printEulerExtend(const vector<pair<int, int>>& previousPath,
    const vector<pair<int, int>>& additionalEdges,
    const vector<pair<int, int>>& newPath) {

    // ��������� ������������ �����
    cout << "��������� ����:\n";
    for (const auto& edge : previousPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;

    // ��������� ���������� �����
    cout << "�������� ����� ��� ����������:\n";
    for (const auto& edge : additionalEdges) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;

    // ��������� ���������� �����
    cout << "��������� ����:\n";
    for (const auto& edge : newPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;
}

// ����� ��� ����������� �������� ���� �����
int Graph::getTotalWeight(const vector<vector<int>>& edges) {
    int totalWeight = 0;
    for (const auto& edge : edges) {
        totalWeight += edge[2]; // The weight is the third element
    }
    return totalWeight;
}

// ������� ��� �������� �������� ����� � �����
bool Graph::edgeExists(int u, int v) {
    for (auto& neighbor : adj[u]) {
        if (neighbor == v) return true;
    }
    return false;
}

// ������� ��� ��������, �� ����� ������� ����� u-v ��������� ������ � ���������� ���
bool Graph::isValidNextEdge(int u, int v)
{
    // ����� u-v � ���������� � ������ � ��������� �������:

    // 1) ���� v � ������ ������� �������� ��� u
    int count = 0; // ��� ��������� ������� ������� ������
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1) // ����������, �� ������� �� ���� �������� (-1)
            count++;
    if (count == 1)
        return true;

    // 2) ���� � ����� ������� ������, ��� u-v �� � ������
    // �������� ������� ����� ��� ��������, �� � u-v ������:

    // 2.a) ������ ������� ������, �������� �� u
    bool* visited = new bool[V];
    memset(visited, false, V * sizeof(bool));
    int count1 = DFSCount(u, visited);

    // 2.b) ��������� ����� (u, v) �� ���� ����� ������
    // ������� ������, �������� �� u
    rmvEdge(u, v);
    memset(visited, false, V * sizeof(bool));
    int count2 = DFSCount(u, visited);

    // 2.c) ������ ����� ����� �� �����
    addEdge(u, v);

    delete[] visited;

    // 2.d) ���� count1 �����, �� count2, ��� ����� (u, v) � ������
    return (count1 > count2) ? false : true;
}

// ������� ��� ��������� ����� u-v � �����. ������� ����� ������ ����� �������� ������ ������� �� -1.
void Graph::rmvEdge(int u, int v)
{
    // ��������� v � ������ �������� u �� �������� ���� �� -1
    list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;

    // ��������� u � ������ �������� v �� �������� ���� �� -1
    list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}

// ������� �� ����� DFS ��� ��������� ������� �������� ������ � v
int Graph::DFSCount(int v, bool visited[])
{
    // ³������ ������� ������� �� �������
    visited[v] = true;
    int count = 1;

    // ���������� �������� �� �������, ����� � ���� ��������
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i]) // ��������, �� ������� ���� �� �� �������
            count += DFSCount(*i, visited);

    return count;
}
