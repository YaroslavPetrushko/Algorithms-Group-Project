// Chinese Postman Problem
// Team 13
// ��-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 12 hour

#include <iostream>
#include <vector>
#include <utility> // ��� std::pair
#include <limits>  // ��� std::numeric_limits
#include "solution.h"
#include "Fleury.h"
#include "Windows.h"

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

// ������� ��� ���������� ��������� ����� �� ���������� ���������� �� ��������
void extendGraph(vector<vector<int>>& e, vector<vector<int>>& previousPath, int& n) {
    int newEdges, u, v, w;

    cout << "������ ������� ����� ������ (���� ���� - ������ 0): ";
    int newNodes;
    cin >> newNodes;

    // If new nodes are added, update the number of vertices in the graph
    n += newNodes;

    cout << "������ ������� ����� ����� ��� ���������� �����: ";
    cin >> newEdges;

    cout << "������ ��� ����� � ������ '������� ����� ����':\n";
    for (int i = 0; i < newEdges; ++i) {
        cin >> u >> v >> w;
        e.push_back({ u, v, w });
    }

    // Add the existing edges from the previous path to the new graph
    for (const auto& edge : previousPath) {
        // Assuming edge is in the form of {start, end, weight}
        e.push_back({ edge[0], edge[1], edge[2] }); // Add previous edges (ensure weight is correct)
    }

    // Recompute the Eulerian path with the augmented graph
    Solution sol;
    auto result = sol.ChinesePostmanProblem(e, n);
    int minDistance = result.first;
    vector<int> eulerCycle = result.second; // Change to vector<int> for vertices

    if (minDistance == -1) {
        cout << "��������� ���������� ���������� �� ���������� �����.\n";
        cout << "������ ������� ���� ����������� � ����.\n";
    }
    else {
        cout << "���������� ����������� ����: " << minDistance << endl;

        Graph g(n);
        // Add edges for the current graph
        for (const auto& edge : e) {
            g.addEdge(edge[0] - 1, edge[1] - 1); // Assuming 0-based index
        }

        cout << "��������� ������� � �����������:\n";
        // Print the Eulerian cycle directly
        for (int vertex : eulerCycle) {
            cout << vertex + 1 << " "; // Print vertices in 1-based index
        }
        cout << endl;

        previousPath = e; // Store the current path for future extensions
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

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Solution sol;
    int n = 0;
    vector<vector<int>> e;
    bool repeat = true;
    bool extendPath = false; // ��������� ����� ��������
    vector<vector<int>> previousPath; // ������ ��� �������� ����

    do {
        // �������� � �����������, �� �������� ���
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
                case '1': // ��������� � �������� '1'
                    cout << "\n����������� ��� ������� 1\n";
                    e = getTemplateData1(n);
                    break; // ������ break ��� ������ � switch
                case '2': // ��������� � �������� '2'
                    cout << "\n����������� ��� ������� 2\n";
                    e = getTemplateData2(n);
                    break; // ������ break ��� ������ � switch
                default: // ���������� ������������ ����
                    cout << "\n������� ���� �������. �������� ����-�����.\n";
                    continue; // ����������� �� ������� �����
                }

                printGraph(e, n); // �������� ����
            }
            else if (choice == '2') {
                e = inputGraph(n); // ������� ���� �� �����������
            }
            else {
                cout << "������� ����. �������� ����-�����.\n";
                continue;
            }

            // ������ chinesePostmanProblem ��� ��������� ���� � ���������� �����
            auto result = sol.ChinesePostmanProblem(e, n);
            int minDistance = result.first;
            vector<int> eulerCycle = result.second; // Ensure this is a vector of integers for vertices

            if (minDistance == -1) {
                cout << "��������� ���������� ������ ���� � �����.\n";
            }
            else {
                cout << "����������� ����: " << minDistance << endl;
                cout << "��������� �������:\n";
                for (int vertex : eulerCycle) {
                    cout << vertex + 1 << " "; // Output the sequence of vertices in 1-based index
                }
                cout << endl;

                previousPath = e; // Store the current path
            }

        }
        else if (mode == '2') {
            if (!previousPath.empty()) {
                extendPath = true;
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

        cout << "��������� �������� (0 - ���, 1 - �)?\n";
        cin >> repeat;

        // Validate the repeat input
        if (repeat != 0 && repeat != 1) {
            cout << "������� ����. ���������� ��������.\n";
            break; // Exit the loop if invalid input
        }

    } while (repeat == 0);

    return 0;
}
