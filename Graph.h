#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string.h>
#include <vector>

using namespace std;

// Клас, що репрезентує граф
class Graph {
    int V; // Кількість вершин
    list<int>* adj; // Динамічний масив списків суміжності

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

    // Функція для виведення графа
    void printGraph(const vector<vector<int>>& e, int n);

    //Функція для запису шляху до файлу CPP_output.txt
    void writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath);

    //Функція для запису оновленого шляху до файлу CPP_extend.txt
    void writeExtendedPathToFile(const vector<vector<int>>& edges, 
        const vector<pair<int, int>>& newPath,
        const vector<pair<int, int>>& additionalEdges);

    // Методи для визначення Ейлерового шляху
    vector<pair<int, int>> getEulerPath(const vector<pair<int, int>>& additionalEdges);
    void getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath);

    //Методи для виведення Ейлерового шляху в консоль
    void printEulerTour(const vector<pair<int, int>>& previousPath);
    void printEulerExtend(const vector<pair<int, int>>& previousPath,
        const vector<pair<int, int>>& additionalEdges,
        const vector<pair<int, int>>& newPath);

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
