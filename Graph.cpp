//���������� ��� �����䳿 � ������, (��������/���������)
// �� ����������� � ��������� ���������� �����
#include "Graph.h"
using namespace std;


// ������� ��� ��������� �����
void Graph::printGraph(const vector<vector<int>>& e, int n) {
    cout << "��� �����.\n";
    cout << "ʳ������ ������: " << n << endl;
    cout << "ʳ������ �����: " << e.size()<< endl;
    cout << "�����:\n";
    for (const auto& edge : e) {
        cout << "������� " << edge[0] << " - ������� "
            << edge[1] << ": ���� " << edge[2] << endl;
    }
}

//������� ��� ������ �������� �� ����� CPP_output.txt
void Graph::writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath) {
    ofstream outFile("CPP_output.txt");
    if (outFile.is_open()) {
        outFile << "ʳ������ ������: " << V << "\n";
        outFile << "ʳ������ �����: " << edges.size() << "\n";

        // ����� �����
        outFile << "�����:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        // ����� ��������
        outFile << "�������:\n";
        for (const auto& edge : eulerPath) {
            outFile << edge.first+1 << " " << edge.second+1 << "\n";
        }

        outFile.close();
    }
}

// ����� ���������� ����� � CPP_extend.txt
void Graph::writeExtendedPathToFile(const vector<vector<int>>& edges,
    const vector<pair<int, int>>& newPath,
    const vector<pair<int, int>>& additionalEdges) {
    std::ofstream outFile("CPP_extend.txt");
    if (outFile.is_open()) {
        outFile << "ʳ������ ������: " << V << "\n";
        outFile << "ʳ������ �����: " << edges.size() << "\n";

        // Write edges in structured format
        outFile << "�����:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        // Write additional edges that complete the Eulerian path
        outFile << "�������� ����������� �����:\n";
        for (const auto& edge : additionalEdges) {
            outFile << edge.first << " " << edge.second << "\n";
        }

        // Write the new Eulerian path in structured format
        outFile << "��������� ����:\n";
        for (const auto& edge : newPath) {
            outFile << edge.first << " " << edge.second << "\n";
        }

        outFile.close();
    }
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
    cout << "����������� ������� :\n";
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
    cout << "�������� ����������� �����:\n";
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

    //����� �������� ��������� � ���� CPP_extend.txt
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

//������� ��� ��������� �����
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
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
