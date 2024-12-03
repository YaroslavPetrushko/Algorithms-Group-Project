#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <string>
#include <vector>
#include <map>
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
    Graph(int V) ;
    ~Graph();

    // Функція для додавання та видалення ребер графу
    void addEdge(int u, int v);
    void rmvEdge(int u, int v);

    // Функція для роботи з перенумерацією вершин графу
    pair<int, vector<vector<int>>> renumberGraph(const vector<vector<int>>& edges, int startPoint);
    vector<pair<int, int>> revertEulerPath(const vector<pair<int, int>>& eulerPath);

    // Функція для виведення графа
    void printGraph(const vector<vector<int>>& e, int n, int startPoint);

    //Функція для запису шляху до файлу CPP_output.txt
    void writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath, int weight,int startPoint, string filename);

    // Методи для визначення Ейлерового шляху
    vector<pair<int, int>> getEulerPath(const vector<pair<int, int>>& additionalEdges, int startPoint);
    void getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath);

    //Метод для виведення Ейлерового шляху в консоль
    void printEulerTour(const vector<pair<int, int>>& previousPath);

    // Функція що повертає кількість досяжних вершин
    int DFSCount(int v, bool visited[]);

    // Допоміжна функції для перевірки, чи є ребро u-v дійсним
    // та чи є наступним ребром у Ейлеровому шляху
    bool edgeExists(int u, int v);
    bool isValidNextEdge(int u, int v);

private:
    vector<pair<int, int>> e; // Вектор для зберігання ребер графа
};
