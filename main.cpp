// Chinese Postman Problem
// Team 13
// ��-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 30 hour

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility> // ��� std::pair
#include <limits>  // ��� std::numeric_limits
#include "Solution.h"
#include "Graph.h"
#include "Windows.h"

using namespace std;

// ������� ��� ���������� ���������� �����
pair<int, vector<vector<int>>> getData(string filename, int& startPoint);

// ������� ��� ������� �������� �����
pair<int, vector<vector<int>>> inputGraph(int& n, int& startPoint);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Solution sol;               // ��'��� ����� Solution, ��� ���������
    vector<vector<int>> edges;  // ����� �����
    int numberOfVertex = 0;     // ʳ������ ������
    int startPoint = 1;         // ��������� ����� ��������
    string filename = "";       // ����� ���������� �����
    int repeat = 1;             // ����� ��� ������� ������ ��������

    do {
        char mode; //����� ��� ������ ������ ������ ��������

        cout << "���� ������ ��������:\n 1 - ���������� ������� �� ����� ����� �����,\n 2 - ������ ��� ������. \n��� ����: "; 
        cin >> mode;

        if (mode == '1') {

            cout << "������� ���� ��� ������ (1, 2, 3): ";
            int fileChoose;
            cin >> fileChoose;
            switch (fileChoose) {
            case 1: filename = "Path_1.txt"; break;
            case 2: filename = "Path_2.txt"; break;
            case 3: filename = "Path_3.txt"; break;
            default: cout << "������� ����.\n"; continue;
            }

            pair<int, vector<vector<int>>> graphData = getData(filename, startPoint);
            numberOfVertex = graphData.first;
            edges = graphData.second;

            Graph graph(numberOfVertex);

            // ���� ����� ��� ����
            graph.printGraph(edges, numberOfVertex, startPoint);
        }
        else if (mode == '2') {
            pair<int, vector<vector<int>>> graphData = inputGraph(numberOfVertex, startPoint);
            numberOfVertex = graphData.first;
            edges = graphData.second;
            filename = "";
            
            if (numberOfVertex == 0 || edges.empty()) {
                cerr << "�������: ���� �� ��������. �������� ��������.\n";
                continue;
            }

            // ��������� ������� ��� ���������� ��������� ������
            set<int> uniqueVertices;

            // ���������� �� �����, ������� �� ������� �� �������
            for (const auto& edge : edges) {
                uniqueVertices.insert(edge[0]); // ������� 1
                uniqueVertices.insert(edge[1]); // ������� 2
            }

            // ��������: ���� ������� ��������� ������ �������� ������ �������
            if (uniqueVertices.size() > numberOfVertex) {
                cerr << "�������: ������ ������� ������ � ������. ���� �� ��������. �������� ��������.\n";
                continue;
            }

        }
        else {
            cerr << "������� ����. �������� ���� �����.\n";
            continue;
        }

        // ������� ����� �������� ���� ��������� �����
        Graph graph(numberOfVertex);

        // ������������� ����� (������� � ���������� ������), ��� ����������� ������������ ���������� ����������
        pair<int, vector<vector<int>>> renumberedData = graph.renumberGraph(edges, startPoint);
        int renumberedStartPoint = renumberedData.first;
        vector<vector<int>> renumberedEdges = renumberedData.second;

        // ������ ������� ��� ����'������ ������
         vector<pair<int, int>> result = sol.chinesePostmanProblem(renumberedEdges, numberOfVertex);
       
         if (result.empty()) {
             cerr << "��������� ���������� �������.\n";
         }
         else {
             // ��������� ����� �� �����
             for (const auto& edge : renumberedEdges) {
                 graph.addEdge(edge[0] - 1, edge[1] - 1);
             }

             // ��������� ���������� �����
             vector<pair<int, int>> eulerPath = graph.getEulerPath(result, renumberedStartPoint);

             // ���������� �� ������� ���������
             vector<pair<int, int>> originalEulerPath = graph.revertEulerPath(eulerPath);

             if (!originalEulerPath.empty()) {
                 // ���������� ���� ��������
                 int pathWeight = sol.calculateRouteWeight(originalEulerPath, edges);
                 cout << "������� ���������� ��������: " << pathWeight << " �����.\n";

                 //���� ���������� � �������
                 graph.printEulerTour(originalEulerPath);

                 // ����� ���������� � ����
                 if (!filename.empty())
                     graph.writePathToFile(edges, originalEulerPath, pathWeight, startPoint, filename);
             }
         }

        //�������� ������ ����������� �� ����� ���������
        cout << "��������� �������� (1 - ���, 0 - �)?\n";
        cin >> repeat;

        if (cin.fail()||repeat!=1&&repeat!=0) {
            cerr << "\n������ ��������. ���������� ��������...\n";
            break;
        }

    } while (repeat==1);

    return 0;
}

// ������� ��� ���������� ����� � ���������� �����
pair<int, vector<vector<int>>> getData(string filename, int& startPoint) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "������� �������� �����.\n";
        return {};  // ��������� ������� ����
    }

    int n, u, v, w;
    file >> n >> startPoint;

    if (file.fail() || n <= 0 || startPoint < 0) {
        cerr << "�������: ����� �������� ��� � ����.\n";
        return {};  // ��������� ������� ����
    }

    vector<vector<int>> edges;

    while (file >> u >> v >> w) {
        if (u < 0 || v < 0 || w < 0) {
            cerr << "�������: ����� ��� ����� � ����.\n";
            return {};  // ��������� ������� ����
        }
        edges.push_back({ u, v, w });
    }
    return { n, edges };
}

// ������� ��� ������� �������� �����
pair<int, vector<vector<int>>> inputGraph(int& n, int& startPoint) {
    cout << "������ ������� �����: ";
    cin >> n;
    cout << "������ ��������� �����: ";
    cin >> startPoint;

    if (n <= 0 || startPoint < 0) {
        cerr << "�������: ������ �������� ������� ������ ��� �������� �����.\n";
        return {};  // ��������� ������� ����
    }

    int edgeCount;
    cout << "������ ������� �����: ";
    cin >> edgeCount;

    if (edgeCount <= 0) {
        cerr << "�������: ������ �������� ������� �����.\n";
        return {};  // ��������� ������� ����
    }

    vector<vector<int>> edges;
    cout << "������ ��� ����� � ������ \"�������1 �������2 ����\" \n";

    for (int i = 0; i < edgeCount; ++i) {
        int u, v, w;
        cout << "����� " << i + 1 << ": ";
        cin >> u >> v >> w;

        if (cin.fail() || u < 1 || v < 1 || w <= 0) {
            cerr << "�������: ������ �������� ��� ����� " << i + 1 << ".\n"<< 
                "������� �� ���� ������ ���� ��������� �������. �������� ��������.\n";
            --i;  // ���������� �������� ��� ����� �����
            continue;
        }

        edges.push_back({ u, v, w });
    }
    return { n, edges };
}
