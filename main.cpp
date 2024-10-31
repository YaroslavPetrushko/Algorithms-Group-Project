// Chinese Postman Problem
// Team 13
// КН-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 6 hour

#include <iostream>
#include <vector>
#include <utility> // Для std::pair
#include <limits>  // Для std::numeric_limits
#include "CPP.h"
#include "Fleury.h"
#include "Windows.h"

using namespace std;

// Функція для перетворення числових індексів у символи
char indexToChar(int index) {
    return 'A' + index; // Перетворює 0 в 'A', 1 в 'B', і т.д.
}

// Функція для зчитування графа від користувача
vector<vector<int>> inputGraph(int& n) {
    cout << "Введіть кількість вершин: ";
    cin >> n;
    int edges;
    cout << "Введіть кількість ребер: ";
    cin >> edges;

    vector<vector<int>> e;
    cout << "Введіть ребра у форматі 'початок кінець вага':\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({ u, v, w });
    }
    return e;
}

// Функція для виведення графа
void printGraph(const vector<vector<int>>& e, int n) {
    cout << "Граф:\n";
    cout << "Кількість вершин: " << n << endl;
    cout << "Ребра:\n";
    for (const auto& edge : e) {
        cout << "Вершина " << indexToChar(edge[0] - 1) << " - Вершина "
            << indexToChar(edge[1] - 1) << ": вага " << edge[2] << endl;
    }
}

// Функція для використання шаблонних даних 1
vector<vector<int>> getTemplateData1(int& n) {
    n = 5; // Кількість точок
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

// Функція для використання шаблонних даних 2
vector<vector<int>> getTemplateData2(int& n) {
    n = 13; // Кількість точок
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
    bool repeat = 0;
    do {
        // Запитуємо у користувача, як отримати дані
        char choice, temp;
        cout << "Використати шаблонні дані (1) чи ввести вручну (2)? Введіть 1 або 2: ";
        cin >> choice;

        if (choice == '1') {
            cout << "\nВибрати шаблон: 1 - приклад, 2 - за реал. ситуацією.\n";
            cin >> temp;
            switch (temp) {
            case '1': // Порівнюємо з символом '1'
                e = getTemplateData1(n);
                break; // Додаємо break для виходу з switch
            case '2': // Порівнюємо з символом '2'
                e = getTemplateData2(n);
                break; // Додаємо break для виходу з switch
            default: // Обробляємо неправильний вибір
                cout << "Невірний вибір шаблону. Повторіть будь-ласка.\n";
                continue; // Повертаємося на початок циклу
            }
            cout << "Використано шаблонні дані:\n";
            printGraph(e, n); // Виводимо граф
        }
        else if (choice == '2') {
            e = inputGraph(n);
        }
        else {
            cout << "Невірний вибір. Повторіть будь-ласка.\n";
            repeat = 0;
            continue;
        }

        // Виклик chinesePostmanProblem для отримання ваги і додаткових ребер
        auto result = sol.chinesePostmanProblem(e, n);
        int minDistance = result.first;
        vector<pair<int, int>> additionalEdges = result.second;

        if (minDistance == -1) {
            cout << "Неможливо побудувати Ейлерів цикл у графі.\n";
        }
        else {
            cout << "Найкоротший шлях: " << minDistance << endl;
            Graph g(n);
            for (const auto& edge : e) {
                g.addEdge(edge[0] - 1, edge[1] - 1);
            }
            cout << "Ейлеровий маршрут:\n";
            g.printEulerTour(additionalEdges); // Додаємо додаткові ребра
        }

        cout << "Повторити програму (0 - так, 1 - ні)?\n";
        cin >> repeat;

    } while (repeat == 0);

    return 0;
}
