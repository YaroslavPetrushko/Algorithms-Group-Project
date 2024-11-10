// Chinese Postman Problem
// Team 13
// ��-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 20 hour

#include <iostream>
#include <vector>
#include <utility> // ��� std::pair
#include <limits>  // ��� std::numeric_limits
#include "Solution.h"
#include "Graph.h"
#include "Windows.h"

using namespace std;

void extendGraph(vector<vector<int>>& e, vector<pair<int, int>>& previousPath, int& n);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Solution sol;
    int n = 0;
    vector<vector<int>> e;
    bool repeat = 0;
    bool extendPath = false; // ��������� ����� ��������
    vector<pair<int, int>> previousPath; // ������ ��� �������� ����

    do {
        char mode,choice, temp;
        cout << "���� ������ ��������: 1 - ���������� ����� ����, 2 - ��������� ��������: ";
        cin >> mode;

        if (mode == '1') {

            previousPath.clear();
            extendPath = false;

            cout << "���� ������� �����: 1 - ����������� ������, 2 - ����� ��������: ";
            cin >> choice;

            if (choice == '1') {
                cout << "���� �������: 1 - �������, 2 - �� ����. ���������: ";
                cin >> temp;
                switch (temp) {
                case '1': 
                    cout << "\n����������� ��� ������� 1\n";
                    e = getTemplateData1(n);
                    break;
                case '2':
                    cout << "\n����������� ��� ������� 2\n";
                    //e = getTemplateData2(n);
                    break;
                default: 
                    cout << "\n������� ���� �������. �������� ����-�����.\n";
                    continue; // ����������� �� ������� �����
                }

                printGraph(e, n); // �������� ����
            }
            else if (choice == '2') {
                e = inputGraph(n); // ���������� ������� ��� �����
            }
            else {
                cout << "������� ����. �������� ����-�����.\n";
                repeat = 0;
                continue;
            }

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
            }

        }
        else if (mode == '2') {
            extendPath = true;
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
        cout << "��������� �������� (0 - ���, 1 - �)?\n";
        cin >> repeat;

    } while (repeat == 0);

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

    // ������ Chinese Postman Problem ��� ���������� ���������� ����� ��� ������� ��������
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

        // �������� ����� ���� �� ������������ �� ���������� �����
        vector<pair<int, int>> newPath = g.getEulerPath(additionalEdges);

        // �������� ��������� ������� �� �����������
        g.printEulerExtend(previousPath, additionalEdges, newPath);
    }
}

