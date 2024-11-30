// Chinese Postman Problem
// Team 13
// КН-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 30 hour

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

// Функція для зчитування текстового файлу
pair<int, vector<vector<int>>> getData(string filename, int& startPoint);

// Функція для ручного введення графу
pair<int, vector<vector<int>>> inputGraph(int& n, int& startPoint);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Solution sol;               // Об'єкт класу Solution, для обчислень
    vector<vector<int>> edges;  // Ребра графу
    int numberOfVertex = 0;     // Кількість вершин
    int startPoint = 1;         // Початкова точка маршруту
    string filename = "";       // Назва текстового файлу
    int repeat = 1;             // Змінна для повтору роботи програми

    do {
        char mode; //Змінна для вибору режиму роботи програми

        cout << "Вибір режиму програми:\n 1 - побудувати маршрут на основі даних файлу,\n 2 - ввести дані вручну. \nВаш вибір: "; 
        cin >> mode;

        if (mode == '1') {

            cout << "Виберіть файл для роботи (1, 2, 3): ";
            int fileChoose;
            cin >> fileChoose;
            switch (fileChoose) {
            case 1: filename = "Path_1.txt"; break;
            case 2: filename = "Path_2.txt"; break;
            case 3: filename = "Path_3.txt"; break;
            default: cout << "Невірний вибір.\n"; continue;
            }

            pair<int, vector<vector<int>>> graphData = getData(filename, startPoint);
            numberOfVertex = graphData.first;
            edges = graphData.second;

            Graph graph(numberOfVertex);

            // Вивід даних про граф
            graph.printGraph(edges, numberOfVertex, startPoint);
        }
        else if (mode == '2') {
            pair<int, vector<vector<int>>> graphData = inputGraph(numberOfVertex, startPoint);
            numberOfVertex = graphData.first;
            edges = graphData.second;
            filename = "";
            
            if (numberOfVertex == 0 || edges.empty()) {
                cerr << "Помилка: Граф не створено. Повторіть введення.\n";
                continue;
            }

            // Створюємо множину для збереження унікальних вершин
            set<int> uniqueVertices;

            // Перебираємо всі ребра, додаючи їх вершини до множини
            for (const auto& edge : edges) {
                uniqueVertices.insert(edge[0]); // Вершина 1
                uniqueVertices.insert(edge[1]); // Вершина 2
            }

            // Перевірка: якщо кількість унікальних вершин перевищує задану кількість
            if (uniqueVertices.size() > numberOfVertex) {
                cerr << "Помилка: Невірна кількість вершин у ребрах. Граф не створено. Повторіть введення.\n";
                continue;
            }

        }
        else {
            cerr << "Невірний вибір. Повторіть будь ласка.\n";
            continue;
        }

        // Основна логіка програми після отримання графу
        Graph graph(numberOfVertex);

        // Перенумерація графу (включно з початковою точкою), для правильного ітераційного обчислення алгоритмом
        pair<int, vector<vector<int>>> renumberedData = graph.renumberGraph(edges, startPoint);
        int renumberedStartPoint = renumberedData.first;
        vector<vector<int>> renumberedEdges = renumberedData.second;

        // Виклик функції для розв'язання задачі
         vector<pair<int, int>> result = sol.chinesePostmanProblem(renumberedEdges, numberOfVertex);
       
         if (result.empty()) {
             cerr << "Неможливо побудувати маршрут.\n";
         }
         else {
             // Додавання ребер до графу
             for (const auto& edge : renumberedEdges) {
                 graph.addEdge(edge[0] - 1, edge[1] - 1);
             }

             // Отримання Ейлерового циклу
             vector<pair<int, int>> eulerPath = graph.getEulerPath(result, renumberedStartPoint);

             // Повернення до вихідної нумерації
             vector<pair<int, int>> originalEulerPath = graph.revertEulerPath(eulerPath);

             if (!originalEulerPath.empty()) {
                 // Обчислення ваги маршруту
                 int pathWeight = sol.calculateRouteWeight(originalEulerPath, edges);
                 cout << "Довжина знайденого маршруту: " << pathWeight << " метрів.\n";

                 //Вивіл результатів в консоль
                 graph.printEulerTour(originalEulerPath);

                 // Запис результатів у файл
                 if (!filename.empty())
                     graph.writePathToFile(edges, originalEulerPath, pathWeight, startPoint, filename);
             }
         }

        //Програма запитує користувача чи треба повторити
        cout << "Повторити програму (1 - так, 0 - ні)?\n";
        cin >> repeat;

        if (cin.fail()||repeat!=1&&repeat!=0) {
            cerr << "\nНевірне введення. Завершення програми...\n";
            break;
        }

    } while (repeat==1);

    return 0;
}

// Функція для зчитування графу з текстового файлу
pair<int, vector<vector<int>>> getData(string filename, int& startPoint) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Помилка відкриття файлу.\n";
        return {};  // Повертаємо порожній граф
    }

    int n, u, v, w;
    file >> n >> startPoint;

    if (file.fail() || n <= 0 || startPoint < 0) {
        cerr << "Помилка: Невірні початкові дані у файлі.\n";
        return {};  // Повертаємо порожній граф
    }

    vector<vector<int>> edges;

    while (file >> u >> v >> w) {
        if (u < 0 || v < 0 || w < 0) {
            cerr << "Помилка: Невірні дані ребра у файлі.\n";
            return {};  // Повертаємо порожній граф
        }
        edges.push_back({ u, v, w });
    }
    return { n, edges };
}

// Функція для ручного введення графу
pair<int, vector<vector<int>>> inputGraph(int& n, int& startPoint) {
    cout << "Введіть кількість точок: ";
    cin >> n;
    cout << "Введіть початкову точку: ";
    cin >> startPoint;

    if (n <= 0 || startPoint < 0) {
        cerr << "Помилка: Невірне введення кількості вершин або стартової точки.\n";
        return {};  // Повертаємо порожній граф
    }

    int edgeCount;
    cout << "Введіть кількість ребер: ";
    cin >> edgeCount;

    if (edgeCount <= 0) {
        cerr << "Помилка: Невірне введення кількості ребер.\n";
        return {};  // Повертаємо порожній граф
    }

    vector<vector<int>> edges;
    cout << "Введіть дані ребер у форматі \"Вершина1 Вершина2 Вага\" \n";

    for (int i = 0; i < edgeCount; ++i) {
        int u, v, w;
        cout << "Ребро " << i + 1 << ": ";
        cin >> u >> v >> w;

        if (cin.fail() || u < 1 || v < 1 || w <= 0) {
            cerr << "Помилка: Невірне введення для ребра " << i + 1 << ".\n"<< 
                "Вершини та вага повинні бути додатними числами. Повторіть введення.\n";
            --i;  // Повторення введення для цього ребра
            continue;
        }

        edges.push_back({ u, v, w });
    }
    return { n, edges };
}
