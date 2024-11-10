// Chinese Postman Problem
// Team 13
// КН-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 20 hour

#include <iostream>
#include <vector>
#include <utility> // Для std::pair
#include <limits>  // Для std::numeric_limits
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
    bool extendPath = false; // Визначаємо режим програми
    vector<pair<int, int>> previousPath; // Зберігає вже існуючий шлях

    do {
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
                case '1': 
                    cout << "\nВикористано дані шаблону 1\n";
                    e = getTemplateData1(n);
                    break;
                case '2':
                    cout << "\nВикористано дані шаблону 2\n";
                    //e = getTemplateData2(n);
                    break;
                default: 
                    cout << "\nНевірний вибір шаблону. Повторіть будь-ласка.\n";
                    continue; // Повертаємося на початок циклу
                }

                printGraph(e, n); // Виводимо граф
            }
            else if (choice == '2') {
                e = inputGraph(n); // Користувач вводить дані графа
            }
            else {
                cout << "Невірний вибір. Повторіть будь-ласка.\n";
                repeat = 0;
                continue;
            }

            // Виклик chinesePostmanProblem для отримання мінімальної довжини і додаткових ребер
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
                
                // Зберігаємо пройдений шлях
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

        //Запит на повторення програми
        cout << "Повторити програму (0 - так, 1 - ні)?\n";
        cin >> repeat;

    } while (repeat == 0);

    return 0;
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

    // Виклик Chinese Postman Problem для обчислення додаткових ребер для повного маршруту
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

