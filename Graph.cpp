//���������� ��� �����䳿 � ������
// �� ����������� � ��������� ���������� �����
#include "Graph.h"
using namespace std;

//������� ��� ������������� ������ �����, (����� � "1,3,24" � "1,2,3")
pair<int, vector<vector<int>>> Graph::renumberGraph(const vector<vector<int>>& edges, int startPoint) {
    //�������� ���� ����� ����� ������
    vertexMapping.clear();
    reverseVertexMapping.clear();

    // ��������, �� � ����������� ������ �������
    set<int> uniqueVertices;
    for (const auto& edge : edges) {
        uniqueVertices.insert(edge[0]);
        uniqueVertices.insert(edge[1]);
    }

    int minVertex = *uniqueVertices.begin();
    int maxVertex = *uniqueVertices.rbegin();

    // ���� ����������� �� �� �������, ����� �� �������
    if (uniqueVertices.size() == (maxVertex - minVertex + 1) && minVertex == 0) {
        this->V = maxVertex + 1;

        return { startPoint, edges }; // ��������� ������ ��� ��� ���
    }

    // ������ �������� �������������
    int currentIndex = 1;
    for (int vertex : uniqueVertices) {
        vertexMapping[vertex] = currentIndex;
        reverseVertexMapping[currentIndex] = vertex;
        currentIndex++;
    }

    // �������������� �������� �����
    int renumberedStartPoint = vertexMapping[startPoint];

    // ��������� ������ ������ ����� �� ���������������� ���������
    vector<vector<int>> renumberedEdges;
    for (const auto& edge : edges) {
        if (vertexMapping.find(edge[0]) == vertexMapping.end() ||
            vertexMapping.find(edge[1]) == vertexMapping.end()) {
            cerr << "�������: ������ �����, ������� �� �������� � ����������.\n";
            return {};  // ��������� ������� ����
        }

        if (edge.size() < 3 || edge[2] < 0) {
            cerr << "�������: ������ ���� �����.\n";
            return {};  // ��������� ������� ����
        }

        renumberedEdges.push_back({
            vertexMapping[edge[0]],
            vertexMapping[edge[1]],
            edge[2] // ���� ����� ���������� ��������
            });
    }

    // ��������� ������� ������ � �����
    this->V = currentIndex - 1;

    return { renumberedStartPoint, renumberedEdges };
}

// ������� ��� ����������� ���������� ����� �������� �� �������� �����
vector<pair<int, int>> Graph::revertEulerPath(const vector<pair<int, int>>& eulerPath) {
    vector<pair<int, int>> revertedPath;

    for (const auto& edge : eulerPath) {
        revertedPath.push_back({
            reverseVertexMapping[edge.first],  // ��������� �� ����������� ������
            reverseVertexMapping[edge.second]  // ��������� �� ����������� ������
            });
    }

    return revertedPath;
}

// ������� ��� ��������� ����� � �������
void Graph::printGraph(const vector<vector<int>>& e, int n, int startPoint) {
    cout << "��� �����.\n����������� ��������� ���� ����� � ��� ����.\n";
    cout << "ʳ������ �������: " << n << endl;
    cout << "ʳ������ ������: " << e.size()<< endl;
    cout << "��������� �����: " << startPoint << endl;
    cout << "������ ��� �����������:\n";

    //����������� ������
    cout << left;  
    cout << setw(20) << "³������� �"
        << setw(20) << "³������� �"
        << "�������" << endl;

    for (const auto& edge : e) {
        cout << setw(20) << edge[0]
            << setw(20) << edge[1]
            << edge[2] << endl;
    }
}

//������� ��� ������ ���������� �� ���������� �����
void Graph::writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath,int weight,int startPoint, string filename) {
    
    // �������� �������� ".txt" �� ���� ���� �����
    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
        filename = filename.substr(0, filename.size() - 4);  // ��������� ".txt"
    }

    // ��������� ��������� "_output.txt" �� ����� �����
    filename += "_output.txt";

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "ʳ������ �������: " << V << "\n";
        outFile << "ʳ������ ������: " << edges.size() << "\n";
        outFile << "��������� �����: " << startPoint << endl;

        // ����� �����
        outFile << "������ ��� �����������:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        outFile << "�������� ������� ��������: " <<weight<< "\n";

        // ����� ��������
        outFile << "����������� �������:\n";
        for (const auto& edge : eulerPath) {
            outFile << edge.first << " " << edge.second << "\n";
        }

        outFile.close();
    }
}

// �����, �� ������� ������ ���� ��� �����
vector<pair<int, int>> Graph::getEulerPath(const vector<pair<int, int>>& additionalEdges, int startPoint) {
    // ������ �������� ����� � ����
    for (const auto& edge : additionalEdges) {
        addEdge(edge.first, edge.second);
    }

    // �������� �� ��������� �������� �����
    if (startPoint-1 < 0 || startPoint >= V) {
        cerr << "�������: �������� ����� " << startPoint << " �� ���� � �����." << endl;
        return {};  // ��������� ������� ����, ��� �������� ����������
    }

    if (adj[startPoint].empty()) {
        cerr << "�������: �������� ����� " << startPoint << " �� �� �������� �����." << endl;
        return {};  // ��������� ������� ����
    }

    // ������ ����� �� ��������������� �����
    vector<pair<int, int>> eulerPath;

    getEulerPathUtil(startPoint, eulerPath);  // ��������� �������� ������� ��� ��������� �����

    // ���� ��������� ���� �� ���������� � startPoint, ������� �������
    if (!eulerPath.empty() && eulerPath.front().first != startPoint) {
        // ��������� ����� �����, ��� ���������� � startPoint
        auto it = find_if(eulerPath.begin(), eulerPath.end(), [&](const pair<int, int>& edge) {
            return edge.first == startPoint;
        });

        if (it != eulerPath.end()) {
            // ��������� �������� ����� � ������� �����
            rotate(eulerPath.begin(), it, eulerPath.end());
        }
    }

    // ����������, �� ���� ����������� �� startPoint
    if (!eulerPath.empty() && eulerPath.back().second != startPoint) {
        // ���� ������ ����� �� ����������� �� startPoint, ������ ����
        eulerPath.push_back({ eulerPath.back().second, startPoint });
    }

    // ���� ���� ������, ��������� ������� ������
    if (eulerPath.empty()) {
        cerr << "�������: ������ ���� �� ��������." << endl;
    }

    return eulerPath;
}

// ��������� ����� getEulerPathUtil ��� �������� ���������� �����.
void Graph::getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath) {
    //�������� �� ������� ������� � ������ ������ �����
    if (u < 0 || u >= V) {
        cerr << "������ ������� " << u + 1 << " �������� �� ��� �����." << endl;
        return;
    }

    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (v != -1 && isValidNextEdge(u, v)) {
            eulerPath.push_back({ u + 1, v + 1 });  // ������ ���� (u, v), ��������� ������� �� 1
            rmvEdge(u, v);
            getEulerPathUtil(v, eulerPath);  // ���������� ��������� ��� �������� �������
        }
    }
}

// ������� �� �������� ������ ������� �� �����
void Graph::printEulerTour(const vector<pair<int, int>>& path) {
    cout << "����������� �������:\n";
    for (const auto& edge : path) {
        cout << edge.first << "-" << edge.second << " ";  // �������� ����, ��� ���������, �� �� �������
    }
    cout << endl;
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

//����������� �����
Graph::Graph(int V)
{
        this->V = V;
        adj = new list<int>[V];
}

//������������� �����
Graph::~Graph()
{
    delete[] adj;
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
    // ��������� v � ������ �������� u
    list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
    if (iv != adj[u].end()) *iv = -1; // ���� ��������, ���������

    // ��������� u � ������ �������� v
    list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
    if (iu != adj[v].end()) *iu = -1; // ���� ��������, ���������
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
