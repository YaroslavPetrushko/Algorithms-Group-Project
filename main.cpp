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

// ������� ��� ������������ ��������� ����� 1
vector<vector<int>> getTemplateData1(int& n) {
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

// ������� ��� ������������ ��������� ����� 2
vector<vector<int>> getTemplateData2(int& n) {
    n = 5; // ʳ������ �����
    return {
        {1, 2, 1300}, // ab - 1300 m
        {1, 10, 550}, // aj - 550
        {2, 3, 350}, // bc - 350
        {3, 4, 150}, // cd - 150
        {3, 11, 500}, // ck - 500
        {4, 5, 500}, // de - 500
        {4, 12, 350}, // dl - 350
        {5, 6, 350}, // ef - 350
        {6, 7, 350},  // fg - 350
        {6, 13, 240},  // fm - 240
        {7, 8, 260},  // gh - 260
        {8, 9, 490},  // hi - 490
        {8, 13, 350},  // hm - 350
        {9, 10, 260},  // ij - 260
        {9, 11, 350},  // ik - 350
        {11, 12, 150},  // kl - 150
        {12, 13, 210}  // lm - 210
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
    int choice, temp;
    cout << "����������� ������� ��� (1) �� ������ ������ (2)? ������ 1 ��� 2: ";
    cin >> choice;

    if (choice == '1') {
        cout << "\n������� ������: 1 - �������, 2 - �� ����. ���������.\n";
        cin >> temp;
        switch (temp) {
        case 1:
            e = getTemplateData1(n);
        case 2:
            e = getTemplateData2(n);
        }
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
