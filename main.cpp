// Chinese Postman Problem
// Team 13
// КН-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 14 hour

#include <iostream>
#include <vector>
#include <utility> // Для std::pair
#include <limits>  // Для std::numeric_limits
#include "Solution.h"
#include "Graph.h"
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
    cout << "Дані графу.\n";
    cout << "Кількість вершин: " << n << endl;
    cout << "Ребра:\n";
    for (const auto& edge : e) {
        cout << "Вершина " << indexToChar(edge[0] - 1) << " - Вершина "
            << indexToChar(edge[1] - 1) << ": вага " << edge[2] << endl;
    }
}

// Функція для доповнення існуючого графа та обчислення доповнення до маршруту
void extendGraph(vector<vector<int>>& e, vector<pair<int, int>>& previousPath, int& n) {
    int newEdges, u, v, w;
    cout << "Введіть кількість нових вершин (якщо немає - введіть 0): ";
    int newNodes;
    cin >> newNodes;

    // Якщо додаються нові вершини, оновлюємо кількість вершин в графі
    n += newNodes;

    cout << "Введіть кількість нових ребер для доповнення графа: ";
    cin >> newEdges;

    cout << "Введіть нові ребра у форматі 'початок кінець вага':\n";
    for (int i = 0; i < newEdges; ++i) {
        cin >> u >> v >> w;
        e.push_back({ u, v, w });
    }

    // Визначаємо, чи можливе доповнення існуючого шляху
    Solution sol;
    auto result = sol.chinesePostmanProblem(e, n);
    int minDistance = result.first;
    vector<pair<int, int>> additionalEdges = result.second;

    if (minDistance == -1) {
        cout << "Неможливо побудувати доповнення до Ейлерового циклу.\n";
        cout << "Повний маршрут потрібно побудувати з нуля.\n";
    }
    else {
        cout << "Доповнений найкоротший шлях: " << minDistance << endl;
        Graph g(n);

        // Додаємо всі ребра з графа для обчислення шляху
        for (const auto& edge : e) {
            g.addEdge(edge[0] - 1, edge[1] - 1);
        }

        // Отримуємо новий шлях із попереднього та додаткових ребер
        vector<pair<int, int>> newPath = g.getEulerPath(additionalEdges);

        // Виводимо оновлений маршрут із доповненням
        g.printEulerExtend(previousPath, additionalEdges, newPath);
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
    bool extendPath = false; // Визначаємо режим програми
    vector<pair<int, int>> previousPath; // Зберігає вже існуючий шлях

    do {
        // Запитуємо у користувача, як отримати дані
        char mode,choice, temp;
        cout << "Вибір режиму програми: 1 - побудувати новий шлях, 2 - доповнити існуючий: ";
        cin >> mode;

        if (mode == '1') {

            previousPath.clear();
            extendPath = false;

            cout << "Вибір вхідних даних: 1 - використати шаблон, 2 - ручне введення: ";
            cin >> choice;

            if (choice == '1') {
                cout << "Вибір шаблону: 1 - приклад, 2 - за реал. ситуацією: ";
                cin >> temp;
                switch (temp) {
                case '1': // Порівнюємо з символом '1'
                    cout << "\nВикористано дані шаблону 1\n";
                    e = getTemplateData1(n);
                    break; // Додаємо break для виходу з switch
                case '2': // Порівнюємо з символом '2'
                    cout << "\nВикористано дані шаблону 2\n";
                    e = getTemplateData2(n);
                    break; // Додаємо break для виходу з switch
                default: // Обробляємо неправильний вибір
                    cout << "\nНевірний вибір шаблону. Повторіть будь-ласка.\n";
                    continue; // Повертаємося на початок циклу
                }

                printGraph(e, n); // Виводимо граф
            }
            else if (choice == '2') {
                e = inputGraph(n); // Зчитуємо граф від користувача
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

                //cout << "Ейлеровий маршрут:\n";
                //g.printEulerTour(additionalEdges); // Додаємо додаткові ребра
                
                // Зберігаємо  пройдений шлях
                previousPath = g.getEulerPath(additionalEdges);  // Зберігаємо шлях, а не всі ребра             

                g.printEulerTour(previousPath);
            }

        }
        else if (mode == '2') {
            extendPath = true;
            if (!previousPath.empty()) {

                extendGraph(e, previousPath, n); // Доповнюємо граф новими даними
            }
            else {
                cout << "Немає існуючого шляху для доповнення. Будь ласка, спочатку побудуйте початковий шлях.\n";
                continue;
            }
        }
        else {
            cout << "Невірний вибір. Повторіть будь-ласка.\n";
            continue;
        }

        cout << "Повторити програму (0 - так, 1 - ні)?\n";
        cin >> repeat;

    } while (repeat == 0);

    return 0;
}
