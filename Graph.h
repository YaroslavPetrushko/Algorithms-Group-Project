#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

// Клас, що репрезентує граф
class Graph {
    int V; // Кількість вершин
    list<int>* adj; // Динамічний масив списків суміжності
    map<int, int> vertexMapping;       // Відображення: вихідний індекс -> новий індекс
    map<int, int> reverseVertexMapping; // Відображення: новий індекс -> вихідний індекс

public:
    // Конструктор та деструктор
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    // Функція для додавання та видалення ребер графу
    void addEdge(int u, int v);
    void rmvEdge(int u, int v);

    // Функція для роботи з перенумерацією
    vector<vector<int>> renumberGraph(const vector<vector<int>>& edges);
    vector<pair<int, int>> revertEulerPath(const vector<pair<int, int>>& eulerPath);

    // Функція для введення даних графу користувачем
    vector<vector<int>> inputGraph(int& n);

    // Функція для виведення графа
    void printGraph(const vector<vector<int>>& e, int n);

    //Функція для запису шляху до файлу CPP_output.txt
    void writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath, string filename);

    // Методи для визначення Ейлерового шляху
    vector<pair<int, int>> getEulerPath(const vector<pair<int, int>>& additionalEdges);
    void getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath);

    //Метод для виведення Ейлерового шляху в консоль
    void printEulerTour(const vector<pair<int, int>>& previousPath);

    //Отримання загальної ваги ребер
    int getTotalWeight(const vector<vector<int>>& edges);

    // Функція що повертає кількість досяжних вершин
    int DFSCount(int v, bool visited[]);

    // Допоміжна функції для перевірки, чи є ребро u-v дійсним
    // та чи є наступним ребром у Ейлеровому шляху
    bool edgeExists(int u, int v);
    bool isValidNextEdge(int u, int v);

private:
    vector<pair<int, int>> e; // Вектор для зберігання ребер графа
};
