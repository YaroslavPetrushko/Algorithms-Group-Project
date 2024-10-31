//Chinese Postman Problem
//Team 13
// ��-37-4
// Algorhythms and Data Structures
// Deadline: 30 November
// Used time: 5 hour

#include <iostream>
#include <vector>
#include <utility> // ��� std::pair
#include <limits>  // ��� std::numeric_limits
#include "CPP.h"
#include "Fleury.h"
#include "Windows.h"

using namespace std;

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
    cout << "����:\n";
    cout << "ʳ������ ������: " << n << endl;
    cout << "�����:\n";
    for (const auto& edge : e) {
        cout << "������� " << edge[0] << " - ������� " << edge[1] << ": ���� " << edge[2] << endl;
    }
}

// ������� ��� ������������ ��������� �����
vector<vector<int>> getTemplateData(int& n) {
    n = 5; // ʳ������ �����
    return {
        {1, 2, 100}, // ab - 100
        {1, 3, 150}, // ac - 150
        {2, 3, 120}, // cb - 120
        {2, 4, 200}, // bd - 200
        {3, 4, 180}, // cd - 180
        {3, 5, 160}, // ce - 160
        {4, 5, 140}  // ed - 140
    };
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Solution sol;
    int n=0;
    vector<vector<int>> e;
    bool repeat = 0;
    do {
    // �������� � �����������, �� �������� ���
    char choice;
    cout << "����������� ������� ��� (1) �� ������ ������ (2)? ������ 1 ��� 2: ";
    cin >> choice;

    if (choice == '1') {
        e = getTemplateData(n);
        cout << "����������� ������� ���:\n";
        printGraph(e, n); // �������� ����
    }
    else if (choice == '2') {
        e = inputGraph(n);
    }
    else {
        cout << "������� ����. �������� ����-�����.\n";
        repeat = 0;
        continue;
    }

    // �������� �������� ������������ �����
    int minDistance = sol.chinesePostmanProblem(e, n);

    // ��������� ���� � �������� �����
    Graph g(n);
    for (const auto& edge : e) {
        g.addEdge(edge[0] - 1, edge[1] - 1); // �������� �� 1 ��� 0-����������
    }

    if (minDistance == -1) {
        cout << "��������� ���������� ������ ���� � �����.\n";
    }
    else {
        cout << "����������� ����: " << minDistance << endl;

        cout << "��������� �������:\n";
        g.printEulerTour();
    }

    cout << "��������� �������� (0 - ���, 1 - �)?\n";
    cin >> repeat;

    } while (repeat == 0);

    return 0;
}
