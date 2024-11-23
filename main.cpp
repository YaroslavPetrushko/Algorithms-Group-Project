// Chinese Postman Problem
// Team 13
// ��-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 25 hour

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

// ��������� ����� ����� �������� ���������� �����
pair<int, vector<vector<int>>> getData(string filename);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int fileChoose; //���� �����
    Solution sol; //г�����
    vector<vector<int>> edges; //�����
    int numberOfVertex = 0; //ʳ������ ������
    string filename; //����� �����
    bool repeat = true, repeatInput=true; //���������� ��������

    do {
        char mode;
        cout << "���� ������ ��������: 1 - ���������� ������� �� ����� ����� �����, 2 - ������ ���� ������: "; //1 - ���������� ����� ���� ���������� ����, 2 - ��������� �������� ���� � ����
        cin >> mode;

        if (mode == '1') {

            cout << "������� ���� ��� ����� ����� (1, 2, 3): ";
            cin >> fileChoose;
            switch (fileChoose) {
            case 0: filename = "CPP.txt"; break;
            case 1: filename = "Path_1.txt"; break;
            case 2: filename = "Path_2.txt"; break;
            case 3: filename = "Path_3.txt"; break;
            default: cout << "������� ����.\n"; continue;
            }

            auto graphData = getData(filename);
            numberOfVertex = graphData.first;
            edges = graphData.second;

            // ��������� �����
            Graph graph(numberOfVertex);
            graph.printGraph(edges, numberOfVertex);

            // ������������� �����
            vector<vector<int>> renumberedEdges = graph.renumberGraph(edges);

            // ������ ������� ��� ����'������ ������
            auto result = sol.chinesePostmanProblem(renumberedEdges, numberOfVertex);
            if (result.first == -1) {
                cout << "��������� ���������� �������.\n";
            }
            else {
                cout << "���������� ������� ��������: " << result.first << " �����.\n";

                for (const auto& edge : renumberedEdges) {
                    graph.addEdge(edge[0]-1, edge[1]-1);
                }

                // ��������� ���������� �����
                vector<pair<int, int>> eulerPath = graph.getEulerPath(result.second);

                // ���������� �� ������� ���������
                vector<pair<int, int>> originalEulerPath = graph.revertEulerPath(eulerPath);

                graph.printEulerTour(originalEulerPath);

                // ����� ���������� � ����
                graph.writePathToFile(edges, originalEulerPath, filename);
            }
        }
        else if (mode == '2') {
            // ����� �������� ����� �����
            Graph graph(numberOfVertex);
            edges = graph.inputGraph(numberOfVertex);

            // ������������� �����
            vector<vector<int>> renumberedEdges = graph.renumberGraph(edges);

            // ������ ������� ��� ����'������ ������
            auto result = sol.chinesePostmanProblem(renumberedEdges, numberOfVertex);
            if (result.first == -1) {
                cout << "��������� ���������� �������.\n";
            }
            else {
                cout << "���������� ������� ��������: " << result.first << " �����.\n";

                for (const auto& edge : edges) {
                    graph.addEdge(edge[0] - 1, edge[1] - 1);
                }

                // ��������� ���������� �����
                vector<pair<int, int>> eulerPath = graph.getEulerPath(result.second);

                // ���������� �� ������� ���������
                vector<pair<int, int>> originalEulerPath = graph.revertEulerPath(eulerPath);

                graph.printEulerTour(originalEulerPath);

                // ����� ���������� � ����
                graph.writePathToFile(edges, originalEulerPath, filename);
            }

        }
        else {
            cout << "������� ����. �������� ����-�����.\n";
            continue;
        }

        //����� �� ���������� ��������
        cout << "��������� �������� (1 - ���, 0 - ��)?\n";
        cin >> repeatInput;

    } while (repeatInput == repeat);

    return 0;
}

// �������, ����� ��������� ���� ��� ��������� ����� ��� ����
pair<int, vector<vector<int>>> getData(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("������� �������� �����");
    }

    vector<vector<int>> edges;
    int n, u, v, w;
    file >> n;
    while (file >> u >> v >> w) {
        edges.push_back({ u, v, w });
    }
    return { n, edges };
}