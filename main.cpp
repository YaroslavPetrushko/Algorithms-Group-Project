// Chinese Postman Problem
// Team 13
// КН-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 20 hour

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility> // Для std::pair
#include <limits>  // Для std::numeric_limits
#include "Solution.h"
#include "Graph.h"
#include "Windows.h"

using namespace std;

//char indexToChar(int index);

// Шаблонні дані для тестування
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
    bool extendPath = false; // Визначаємо режим програми
    vector<pair<int, int>> previousPath; // Зберігає вже існуючий шлях

    do {
        char mode, choice, temp;
        if (extendPath)
        cout << "Вибір режиму програми: 1 - побудувати новий шлях, 2 - доповнити існуючий: "; //1 - побудувати новий шлях відкриваючи файл, 2 - доповнити існуючий шлях у файлі
        else 
            cout << "Вибір режиму програми: 1 - побудувати новий шлях: "; //1 - побудувати новий шлях відкриваючи файл

        cin >> mode;

        if (mode == '1') {

            previousPath.clear();
            extendPath = false;

            cout << "\nВикористано дані з текстового файлу CPP.txt\n";

            e = getData(n); // Читаємо текстовий файл CPP.txt 

            g.printGraph(e, n); // Виводимо граф

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

                //Запис результатів до файлу CPP_output.txt
                g.writePathToFile(e, previousPath);

                extendPath = true;
            }
        }
        else if (extendPath&&mode == '2') {
            
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
        cout << "Повторити програму (1 - так, 0 - ні)?\n";
        cin >> repeat;

    } while (repeat == 1);

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

    // Виклик CPP для обчислення додаткових ребер для повного маршруту
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

        // Будуємо новий шлях із попереднього шляху та додаткових ребер
        vector<pair<int, int>> newPath = g.getEulerPath(additionalEdges);

        // Виводимо оновлений маршрут із доповненням
        g.printEulerExtend(previousPath, additionalEdges, newPath);

        //Запис результатів до CPP_extend.txt
        g.writeExtendedPathToFile(e, newPath, additionalEdges);
    }
}

//// Функція для перетворення числових індексів у символи
//char indexToChar(int index) {
//    return 'A' + index; // Перетворює 0 в 'A', 1 в 'B', і т.д.
//}

// Функція, зчитує текстовий файл для отримання даних про граф
vector<vector<int>> getData(int& n) {
    std::ifstream file("CPP.txt"); // назва файлу може змінюватися відповідно до вимог
    if (!file.is_open()) {
        throw std::runtime_error("Помилка відкриття файлу");
    }

    vector<vector<int>> edges;
    file >> n;  // перший рядок містить кількість точок
    int u, v, w;

    while (file >> u >> v >> w) {
        edges.push_back({ u, v, w });
    }
    file.close();
    return edges;
}