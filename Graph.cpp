//���������� ��� �����䳿 � ������, (��������/���������)
// �� ����������� � ��������� ���������� �����
#include "Graph.h"
using namespace std;

vector<vector<int>> Graph::renumberGraph(const vector<vector<int>>& edges) {
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
        return edges; // ��������� ������ ����� ��� ���
    }

    // ������ �������� �������������
    int currentIndex = 1;
    for (int vertex : uniqueVertices) {
        vertexMapping[vertex] = currentIndex;
        reverseVertexMapping[currentIndex] = vertex;
        currentIndex++;
    }

    // ��������� ������ ������ ����� �� ���������������� ���������
    vector<vector<int>> renumberedEdges;
    for (const auto& edge : edges) {
        if (vertexMapping.find(edge[0]) == vertexMapping.end() ||
            vertexMapping.find(edge[1]) == vertexMapping.end()) {
            throw std::runtime_error("Invalid edge: vertex not found in mapping");
        }

        renumberedEdges.push_back({
            vertexMapping[edge[0]],
            vertexMapping[edge[1]],
            edge[2] // ���� ����� ���������� ��������
            });
    }

    // ��������� ������� ������ � �����
    this->V = currentIndex-1;

    return renumberedEdges;
}

// ������� ��� ����������� ���������� ����� �������� �� �������� �����
vector<pair<int, int>> Graph::revertEulerPath(const vector<pair<int, int>>& eulerPath) {
    vector<pair<int, int>> revertedPath;

    for (const auto& edge : eulerPath) {
        revertedPath.push_back({
            reverseVertexMapping[edge.first+1],  // ��������� �� ����������� ������
            reverseVertexMapping[edge.second+1]  // ��������� �� ����������� ������
            });
    }

    return revertedPath;
}

//// ������� ��� ������� �������� �����
//pair<int, vector<vector<int>>> Graph::inputGraph(int& n) {
//    cout << "������ ������� �����: ";
//    cin >> n;
//    int edges;
//    cout << "������ ������� ������: ";
//    cin >> edges;
//    vector<vector<int>> e;
//    cout << "������ ��� ����� � ������ \"�������1 �������2 ����_�����\":\n";
//    for (int i = 0; i < edges; ++i) {
//        int u, v, w;
//        cin >> u >> v >> w;
//
//        if ( u < 0 || v < 0) {
//            throw std::invalid_argument("������� ������� �������.");
//        }
//
//        e.push_back({ u, v, w });
//    }
//    return { n,e };
//}

// ������� ��� ��������� �����
void Graph::printGraph(const vector<vector<int>>& e, int n) {
    cout << "��� �����.\n����������� ��������� ���� ����� � ��� ����\n";
    cout << "ʳ������ �������: " << n << endl;
    cout << "ʳ������ ������: " << e.size()<< endl;
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

//������� ��� ������ �������� �� ����� CPP_output.txt
void Graph::writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath, string filename) {
    
    // �������� �������� ".txt" �� ���� ���� �����
    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
        filename = filename.substr(0, filename.size() - 4);  // ��������� ".txt"
    }

    // ��������� �������� "_output" � ���������� ".txt"
    filename += "_output.txt";

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "ʳ������ �������: " << V << "\n";
        outFile << "ʳ������ ������: " << edges.size() << "\n";

        // ����� �����
        outFile << "������ ��� �����������:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        // ����� ��������
        outFile << "����������� �������:\n";
        for (const auto& edge : eulerPath) {
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
void Graph::printEulerTour(const vector<pair<int, int>>& path) {
    cout << "����������� ������� �� ���������� :\n";
    for (const auto& edge : path) {
        cout << edge.first << "-" << edge.second << " ";  // �������� ����, ��� ���������, �� �� �������
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

Graph::Graph(int V)
{
        this->V = V;
        adj = new list<int>[V];
}

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
