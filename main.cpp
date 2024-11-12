// Chinese Postman Problem
// Team 13
// ��-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 20 hour

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

//char indexToChar(int index);

// ������� ��� ��� ����������
vector<vector<int>> getData(int& n);

void extendGraph(vector<vector<int>>& e, vector<pair<int, int>>& previousPath, int& n);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n = 0;
    Solution sol;
    Graph g(n);
    vector<vector<int>> e;
    bool repeat = 1;
    bool extendPath = false; // ��������� ����� ��������
    vector<pair<int, int>> previousPath; // ������ ��� �������� ����

    do {
        char mode, choice, temp;
        if (extendPath)
        cout << "���� ������ ��������: 1 - ���������� ����� ����, 2 - ��������� ��������: "; //1 - ���������� ����� ���� ���������� ����, 2 - ��������� �������� ���� � ����
        else 
            cout << "���� ������ ��������: 1 - ���������� ����� ����: "; //1 - ���������� ����� ���� ���������� ����

        cin >> mode;

        if (mode == '1') {

            previousPath.clear();
            extendPath = false;

            cout << "\n����������� ��� � ���������� ����� CPP.txt\n";

            e = getData(n); // ������ ��������� ���� CPP.txt 

            g.printGraph(e, n); // �������� ����

            // ������ chinesePostmanProblem ��� ��������� �������� ������� � ���������� �����
            auto result = sol.chinesePostmanProblem(e, n);
            int minDistance = result.first;
            vector<pair<int, int>> additionalEdges = result.second;

            if (minDistance == -1) {
                cout << "��������� ���������� ������ ���� � �����.\n";
            }
            else {
                cout << "����������� ����: " << minDistance << endl;
                Graph g(n);
                for (const auto& edge : e) {
                    g.addEdge(edge[0] - 1, edge[1] - 1);
                }

                // �������� ��������� ����
                previousPath = g.getEulerPath(additionalEdges);  // �������� ����, � �� �� �����             

                g.printEulerTour(previousPath);

                //����� ���������� �� ����� CPP_output.txt
                g.writePathToFile(e, previousPath);

                extendPath = true;
            }
        }
        else if (extendPath&&mode == '2') {
            
            if (!previousPath.empty()) {
                extendGraph(e, previousPath, n); // ���������� ���� ������ ������
            }
            else {
                cout << "���� ��������� ����� ��� ����������. ���� �����, �������� ��������� ���������� ����.\n";
                continue;
            }
        }
        else {
            cout << "������� ����. �������� ����-�����.\n";
            continue;
        }

        //����� �� ���������� ��������
        cout << "��������� �������� (1 - ���, 0 - �)?\n";
        cin >> repeat;

    } while (repeat == 1);

    return 0;
}

// ������� ��� ���������� ��������� ����� �� ���������� ���������� �� ��������
void extendGraph(vector<vector<int>>& e, vector<pair<int, int>>& previousPath, int& n) {
    int newEdges, u, v, w;
    cout << "������ ������� ����� ������ (���� ���� - ������ 0): ";
    int newNodes;
    cin >> newNodes;

    // ���� ��������� ��� �������, ��������� ������� ������ � �����
    n += newNodes;

    cout << "������ ������� ����� ����� ��� ���������� �����: ";
    cin >> newEdges;

    cout << "������ ��� ����� � ������ '������� ����� ����':\n";
    for (int i = 0; i < newEdges; ++i) {
        cin >> u >> v >> w;
        e.push_back({ u, v, w });
    }

    // ������ CPP ��� ���������� ���������� ����� ��� ������� ��������
    Solution sol;
    auto result = sol.chinesePostmanProblem(e, n);
    int minDistance = result.first;
    vector<pair<int, int>> additionalEdges = result.second;

    if (minDistance == -1) {
        cout << "��������� ���������� ���������� �� ���������� �����.\n";
        cout << "������ ������� ������� ���������� � ����.\n";
    }
    else {
        cout << "���������� ����������� ����: " << minDistance << endl;
        Graph g(n);

        // ������ �� ����� � ����� ��� ���������� �����
        for (const auto& edge : e) {
            g.addEdge(edge[0] - 1, edge[1] - 1);
        }

        // ������ ����� ���� �� ������������ ����� �� ���������� �����
        vector<pair<int, int>> newPath = g.getEulerPath(additionalEdges);

        // �������� ��������� ������� �� �����������
        g.printEulerExtend(previousPath, additionalEdges, newPath);

        //����� ���������� �� CPP_extend.txt
        g.writeExtendedPathToFile(e, newPath, additionalEdges);
    }
}

//// ������� ��� ������������ �������� ������� � �������
//char indexToChar(int index) {
//    return 'A' + index; // ���������� 0 � 'A', 1 � 'B', � �.�.
//}

// �������, ����� ��������� ���� ��� ��������� ����� ��� ����
vector<vector<int>> getData(int& n) {
    std::ifstream file("CPP.txt"); // ����� ����� ���� ���������� �������� �� �����
    if (!file.is_open()) {
        throw std::runtime_error("������� �������� �����");
    }

    vector<vector<int>> edges;
    file >> n;  // ������ ����� ������ ������� �����
    int u, v, w;

    while (file >> u >> v >> w) {
        edges.push_back({ u, v, w });
    }
    file.close();
    return edges;
}