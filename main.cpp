// Chinese Postman Problem
// Team 13
// КН-37-4
// Algorhythms and Data Structures
// Deadline: 28 November
// Used time: 25 hour

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

// Отримання даних через відкриття текстового файлу
pair<int, vector<vector<int>>> getData(string filename);

// Ручне введення даних
pair<int, vector<vector<int>>> inputGraph(int& n);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int fileChoose; //Вибір файлу
    Solution sol; //Рішення
    vector<vector<int>> edges; //Ребра
    int numberOfVertex = 0; //Кількість вершин
    string filename; //Назва файлу
    bool repeat = true, repeatInput=true; //Повторення програми

    do {
        char mode;
        cout << "Вибір режиму програми: 1 - побудувати маршрут на основі даних файлу, 2 - ввести дані вручну: "; //1 - побудувати новий шлях відкриваючи файл, 2 - доповнити існуючий шлях у файлі
        cin >> mode;

        if (mode == '1') {

            cout << "Виберіть файл для даних графу (1, 2, 3): ";
            cin >> fileChoose;
            switch (fileChoose) {
            case 1: filename = "Path_1.txt"; break;
            case 2: filename = "Path_2.txt"; break;
            case 3: filename = "Path_3.txt"; break;
            default: cout << "Невірний вибір.\n"; continue;
            }

            pair<int, vector<vector<int>>> graphData = getData(filename);
            numberOfVertex = graphData.first;
            edges = graphData.second;

            // Виведення графу
            Graph graph(numberOfVertex);
            graph.printGraph(edges, numberOfVertex);

            // Перенумерація графа
            vector<vector<int>> renumberedEdges = graph.renumberGraph(edges);

            // Виклик функції для розв'язання задачі
            pair<int, vector<pair<int, int>>> result = sol.chinesePostmanProblem(renumberedEdges, numberOfVertex);
            if (result.first == -1) {
                cout << "Неможливо побудувати маршрут.\n";
            }
            else {
                cout << "Оптимальна довжина маршруту: " << result.first << " метрів.\n";

                for (const auto& edge : renumberedEdges) {
                    graph.addEdge(edge[0]-1, edge[1]-1);
                }

                // Отримання Ейлерового циклу
                vector<pair<int, int>> eulerPath = graph.getEulerPath(result.second);

                // Повернення до вихідної нумерації
                vector<pair<int, int>> originalEulerPath = graph.revertEulerPath(eulerPath);

                graph.printEulerTour(originalEulerPath);

                // Запис результатів у файл
                graph.writePathToFile(edges, originalEulerPath, filename);
            }
        }
        else if (mode == '2') {

            pair<int, vector<vector<int>>> graphData = inputGraph(numberOfVertex);
            numberOfVertex = graphData.first;
            edges = graphData.second;

            // ручне введення даних графу
            Graph graph(numberOfVertex);

            // Перенумерація графа
            vector<vector<int>> renumberedEdges = graph.renumberGraph(edges);

            // Виклик функції для розв'язання задачі
            pair<int, vector<pair<int, int>>> result = sol.chinesePostmanProblem(renumberedEdges, numberOfVertex);
            if (result.first == -1) {
                cout << "Неможливо побудувати маршрут.\n";
            }
            else {
                cout << "Оптимальна довжина маршруту: " << result.first << " метрів.\n";

                for (const auto& edge : renumberedEdges) {
                    graph.addEdge(edge[0]-1, edge[1]-1);
                }

                // Отримання Ейлерового циклу
                vector<pair<int, int>> eulerPath = graph.getEulerPath(result.second);

                // Повернення до вихідної нумерації
                vector<pair<int, int>> originalEulerPath = graph.revertEulerPath(eulerPath);

                graph.printEulerTour(originalEulerPath);

            }

        }
        else {
            cout << "Невірний вибір. Повторіть будь-ласка.\n";
            continue;
        }

        //Запит на повторення програми
        cout << "Повторити програму (1 - так, 0 - ні)?\n";
        cin >> repeatInput;

    } while (repeatInput == repeat);

    return 0;
}

// Функція, зчитує текстовий файл для отримання даних про граф
pair<int, vector<vector<int>>> getData(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Помилка відкриття файлу");
    }

    vector<vector<int>> edges;
    int n, u, v, w;
    file >> n;
    while (file >> u >> v >> w) {
        edges.push_back({ u, v, w });
    }
    return { n, edges };
}

// Функція для ручного введення графу
pair<int, vector<vector<int>>> inputGraph(int& n) {
    cout << "Введіть кількість точок: ";
    cin >> n;
    int edges;
    cout << "Введіть кількість вулиць: ";
    cin >> edges;
    vector<vector<int>> e;
    cout << "Введіть дані графу у форматі \"Вершина1 Вершина2 Вага_ребра\":\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 0 || v < 0) {
            throw std::invalid_argument("Введено недійсну вершину.");
        }

        e.push_back({ u, v, w });
    }
    return { n,e };
}